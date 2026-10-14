#include <cstdint>
#include <cstdio>
extern "C" void ext_dct8_eval(void*, uint64_t*, const uint64_t*, uint64_t);
int main(){
  // single sample probes
  for (int x=0;x<3;x++){
    uint64_t ins[4]={ (uint64_t)1 << (8*x),1,0,0}, outs[4];
    ext_dct8_eval(nullptr,outs,ins,0);
    printf("x=%d lane0=%04x lane1=%04x\n", x, (unsigned)(outs[0]&0xFFFF), (unsigned)((outs[0]>>16)&0xFFFF));
  }
}
