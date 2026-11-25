// Load-balance probe/regression for the pyc_parallel_for dispatch pool.
//
// Usage:
//   tp_balance [filter]   measure: print an efficiency table
//                         (filter keeps scenarios whose name contains it)
//   tp_balance --check    regression: self-validating thresholds, exit != 0
//                         on failure, exit 0 with "skip" on single-core hosts
//
// Metrics per scenario:
//   ideal = sum(part costs) / claimers   (claimers = workers + dispatching main)
//   wall  = best dispatch wall time over reps
//   eff   = ideal / wall                 (1.0 = perfectly balanced)
//
// PYC_TP_STATS=1 additionally prints a per-thread (parts / busy / share)
// table at exit; without it the probe costs one relaxed load per dispatch.
//
// Scenarios model parallel-tick dispatch shapes:
//   uniform  - every instance equally expensive
//   skew     - every 8th instance 10x heavier (hot modules)
//   onetail  - one instance dominates (single fat top module)
//   chunk9/2 - tickChunkInstances granularity: parts are chunks of 1ms instances
#include "cpp/pyc_thread_pool.hpp"

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <string>
#include <thread>

using clk = std::chrono::steady_clock;

static void spinMs(double ms) {
  const auto end =
      clk::now() + std::chrono::microseconds(static_cast<long long>(ms * 1000));
  while (clk::now() < end) {
  }
}

struct Scenario {
  const char *name;
  unsigned parts;
  double (*costMs)(unsigned);
};

static const Scenario kScenarios[] = {
    {"uniform", 32, [](unsigned) { return 2.0; }},
    {"skew", 32, [](unsigned i) { return i % 8 == 0 ? 10.0 : 1.0; }},
    {"onetail", 32, [](unsigned i) { return i == 0 ? 40.0 : 1.0; }},
    {"chunk9", 8, [](unsigned i) { return i < 7 ? 9.0 : 1.0; }},
    {"chunk2", 32, [](unsigned) { return 2.0; }},
};

static const unsigned kScenarioCount =
    sizeof(kScenarios) / sizeof(kScenarios[0]);

static double runScenario(const Scenario &sc, unsigned claimers, unsigned reps) {
  double totalCost = 0;
  for (unsigned i = 0; i < sc.parts; ++i)
    totalCost += sc.costMs(i);
  double best = 1e9;
  for (unsigned r = 0; r < reps; ++r) {
    const auto t0 = clk::now();
    pyc::cpp::pyc_parallel_for(sc.parts,
                               [&](unsigned i) { spinMs(sc.costMs(i)); });
    best = std::min(
        best, std::chrono::duration<double, std::milli>(clk::now() - t0).count());
  }
  const double ideal = totalCost / claimers;
  const double eff = ideal / best;
  std::printf("%-8s parts=%-2u cost=%4.0fms ideal=%6.1fms wall=%6.1fms eff=%5.1f%%\n",
              sc.name, sc.parts, totalCost, ideal, best, 100.0 * eff);
  return eff;
}

int main(int argc, char **argv) {
  const bool check = argc > 1 && std::strcmp(argv[1], "--check") == 0;
  const char *filter = check ? nullptr : (argc > 1 ? argv[1] : nullptr);

  if (check) {
    unsigned hw = std::thread::hardware_concurrency();
    unsigned threads = hw == 0 ? 1u : std::min(4u, hw);
    if (threads < 2) {
      std::printf("skip: load-balance check needs >=2 cores\n");
      return 0;
    }
    // Pin the pool size before the first dispatch creates the pool.
    pyc::cpp::pyc_set_threads(threads);
  }
  const unsigned resolved = pyc::cpp::pyc_threads();
  const unsigned claimers = resolved ? resolved + 1 : 1;
  const unsigned reps = check ? 3 : 5;

  // Warm the pool once so first-dispatch wakeups don't skew the first rep.
  pyc::cpp::pyc_parallel_for(8, [](unsigned) { spinMs(0.2); });

  if (!check)
    std::printf("threads=%u claimers=%u reps=%u (wall = best of reps)\n",
                resolved, claimers, reps);

  double eff[kScenarioCount] = {0};
  for (unsigned s = 0; s < kScenarioCount; ++s) {
    const Scenario &sc = kScenarios[s];
    if (filter && std::string(sc.name).find(filter) == std::string::npos)
      continue;
    eff[s] = runScenario(sc, claimers, reps);
  }
  if (!check)
    return 0;

  struct Check {
    const char *desc;
    bool ok;
  };
  const double eUniform = eff[0], eSkew = eff[1], eOneTail = eff[2];
  const double eChunk9 = eff[3], eChunk2 = eff[4];
  const Check checks[] = {
      {"uniform load eff >= 70% (dynamic claim spreads even parts)",
       eUniform >= 0.70},
      {"skewed load eff >= 60% (heavy parts get absorbed by idle threads)",
       eSkew >= 0.60},
      {"single-fat-part eff <= 70% (probe still detects real imbalance)",
       eOneTail > 0.0 && eOneTail <= 0.70},
      {"fine chunks (chunk=2) eff >= 70%",
       eChunk2 >= 0.70},
      {"fine chunks never balance much worse than coarse (chunk=9)",
       eChunk2 + 0.05 >= eChunk9},
  };
  bool ok = true;
  for (const Check &c : checks) {
    std::printf("%s: %s\n", c.ok ? "ok" : "FAIL", c.desc);
    ok = ok && c.ok;
  }
  return ok ? 0 : 1;
}
