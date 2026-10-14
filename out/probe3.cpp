#include <cstdint>
#include <cstdio>
extern "C" void ext_dct8_eval(void*, uint64_t*, const uint64_t*, uint64_t);
int main(){
  uint64_t ins[4]={1,0,0,0}, outs[8];
  ext_dct8_eval(nullptr,outs,ins,0);
  printf("%016llx\n",(unsigned long long)outs[0]);
}
