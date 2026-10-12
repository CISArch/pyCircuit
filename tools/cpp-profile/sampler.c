// pycprof: LD_PRELOAD 用户态采样 profiler
// 目的:容器内 perf_event_paranoid=4 无法使用 perf_event_open 时,
// 用 ITIMER_PROF + SIGPROF 采样 CPU 时间,手工走 frame pointer 回栈。
// 依赖被测二进制使用 -fno-omit-frame-pointer 编译(见 PYC_REPLAY_OPT)。
//
// 环境变量:
//   PYCPROF_OUT   输出样本文件路径(必填),maps 写同名 .maps,元数据写同名 .meta
//   PYCPROF_HZ    采样频率(默认 2000/s)
//   PYCPROF_DEPTH 最大栈深(默认 64)
//
// 文件格式(小端):
//   header: magic[8]="PYCPROF1" | u32 version | u32 max_depth | u64 interval_ns | u32 path_len | path bytes
//   record: u64 ts_ns | u32 n | u32 pad | n * u64 pc
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
#include <ucontext.h>
#include <limits.h>

#define MAGIC "PYCPROF1"
#define VERSION 1u

static int g_fd = -1;
static uint32_t g_max_depth = 64;
static uint64_t g_interval_ns = 500000ull;
static volatile uint64_t g_samples = 0;
static volatile uint64_t g_dropped = 0;
static uint64_t g_stack_low = 0;
static uint64_t g_stack_high = 0;
static char g_out[PATH_MAX];
static char g_exe[PATH_MAX];
static int g_started = 0;

static uint64_t now_ns(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint64_t)ts.tv_sec * 1000000000ull + (uint64_t)ts.tv_nsec;
}

static void write_all(int fd, const void *buf, size_t len) {
  const char *p = (const char *)buf;
  while (len > 0) {
    ssize_t n = write(fd, p, len);
    if (n <= 0) return;
    p += n;
    len -= (size_t)n;
  }
}

// 从 /proc/self/maps 取 [stack] 区间,用于校验 frame pointer 合法性
static void find_stack_bounds(void) {
  FILE *f = fopen("/proc/self/maps", "r");
  if (!f) return;
  char line[512];
  while (fgets(line, sizeof(line), f)) {
    if (!strstr(line, "[stack]")) continue;
    unsigned long lo = 0, hi = 0;
    if (sscanf(line, "%lx-%lx", &lo, &hi) == 2) {
      g_stack_low = lo;
      g_stack_high = hi;
    }
  }
  fclose(f);
}

static void dump_maps(void) {
  if (g_out[0] == '\0') return;
  char path[PATH_MAX + 8];
  snprintf(path, sizeof(path), "%s.maps", g_out);
  FILE *dst = fopen(path, "w");
  if (!dst) return;
  FILE *src = fopen("/proc/self/maps", "r");
  if (src) {
    char line[1024];
    while (fgets(line, sizeof(line), src)) fputs(line, dst);
    fclose(src);
  }
  fclose(dst);

  snprintf(path, sizeof(path), "%s.meta", g_out);
  dst = fopen(path, "w");
  if (dst) {
    fprintf(dst,
            "{\"sampler\":\"pycprof\",\"version\":%u,\"interval_ns\":%llu,"
            "\"hz\":%.3f,\"max_depth\":%u,\"samples\":%llu,\"dropped\":%llu,"
            "\"stack_low\":%llu,\"stack_high\":%llu,\"exe\":\"%s\"}\n",
            VERSION, (unsigned long long)g_interval_ns,
            g_interval_ns ? 1e9 / (double)g_interval_ns : 0.0, g_max_depth,
            (unsigned long long)g_samples, (unsigned long long)g_dropped,
            (unsigned long long)g_stack_low, (unsigned long long)g_stack_high,
            g_exe);
    fclose(dst);
  }
}

static void handler(int sig, siginfo_t *si, void *uc) {
  (void)sig;
  (void)si;
  ucontext_t *ctx = (ucontext_t *)uc;
  uint64_t pc = (uint64_t)ctx->uc_mcontext.gregs[REG_RIP];
  uint64_t bp = (uint64_t)ctx->uc_mcontext.gregs[REG_RBP];
  uint64_t ts = now_ns();

  uint64_t pcs[256];
  uint32_t n = 0;
  if (g_max_depth > 256) g_max_depth = 256;
  pcs[n++] = pc;

  // 手工走 frame pointer 链: [rbp] = 上一层 rbp, [rbp+8] = 返回地址
  uint64_t frame = bp;
  while (n < g_max_depth) {
    if (frame == 0 || (frame & 0x7) != 0) break;
    if (g_stack_low && (frame < g_stack_low || frame + 16 > g_stack_high)) break;
    uint64_t next = *(uint64_t *)frame;
    uint64_t ret = *(uint64_t *)(frame + 8);
    if (ret == 0) break;
    pcs[n++] = ret;
    if (next <= frame) break;  // 必须向高地址前进
    frame = next;
  }

  struct {
    uint64_t ts;
    uint32_t n;
    uint32_t pad;
    uint64_t pcs[256];
  } rec;
  rec.ts = ts;
  rec.n = n;
  rec.pad = 0;
  memcpy(rec.pcs, pcs, n * sizeof(uint64_t));

  size_t bytes = sizeof(uint64_t) * 2 + n * sizeof(uint64_t);
  if (g_fd >= 0) write_all(g_fd, &rec, bytes);
  g_samples++;
}

__attribute__((constructor)) static void pycprof_init(void) {
  const char *out = getenv("PYCPROF_OUT");
  if (!out || !*out) return;
  snprintf(g_out, sizeof(g_out), "%s", out);
  if (const char *hz = getenv("PYCPROF_HZ")) {
    double v = atof(hz);
    if (v > 0) g_interval_ns = (uint64_t)(1e9 / v);
  }
  if (const char *d = getenv("PYCPROF_DEPTH")) {
    uint32_t v = (uint32_t)atoi(d);
    if (v > 0) g_max_depth = v;
  }
  ssize_t k = readlink("/proc/self/exe", g_exe, sizeof(g_exe) - 1);
  if (k > 0) g_exe[k] = '\0';

  g_fd = open(g_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (g_fd < 0) return;

  uint32_t path_len = (uint32_t)strlen(g_exe);
  write_all(g_fd, MAGIC, 8);
  write_all(g_fd, &(uint32_t){VERSION}, 4);
  write_all(g_fd, &g_max_depth, 4);
  write_all(g_fd, &g_interval_ns, 8);
  write_all(g_fd, &path_len, 4);
  write_all(g_fd, g_exe, path_len);

  find_stack_bounds();

  // 预热:第一次 walk 可能触发 lazy 解析,放在安装定时器之前
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_sigaction = handler;
  sa.sa_flags = SA_SIGINFO | SA_RESTART;
  sigemptyset(&sa.sa_mask);
  if (sigaction(SIGPROF, &sa, NULL) != 0) {
    close(g_fd);
    g_fd = -1;
    return;
  }
  struct itimerval it;
  memset(&it, 0, sizeof(it));
  it.it_interval.tv_sec = (time_t)(g_interval_ns / 1000000000ull);
  it.it_interval.tv_usec = (suseconds_t)((g_interval_ns % 1000000000ull) / 1000ull);
  it.it_value = it.it_interval;
  if (setitimer(ITIMER_PROF, &it, NULL) != 0) {
    close(g_fd);
    g_fd = -1;
    return;
  }
  g_started = 1;
  atexit(dump_maps);
}
