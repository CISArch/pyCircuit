#include <cstdint>
#include <cstdio>
extern "C" void ext_dct8_eval(void*, uint64_t*, const uint64_t*, uint64_t);
int main(){ uint64_t outs[4], ins[4];
  const uint64_t vecs[3]={0x0807060504030201ull,0,0xFF00FF00FF00FF00ull};
  for(int i=0;i<3;i++){ ins[0]=vecs[i]; ins[1]=1;
    ext_dct8_eval(nullptr,outs,ins,i); printf("%016llx\n",(unsigned long long)outs[0]); } }
