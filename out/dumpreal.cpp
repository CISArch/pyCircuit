#include <cstdint>
#include <cstdio>
#define main dct8_unused_main
#include "../designs/examples/ext_dct8/ext/dct8.cpp"
#undef main
int main(){
  for(int u=0;u<2;++u){
    for(int x=0;x<8;++x) printf("%d ", (int)kCoef[u*8+x]);
    printf("\n");
  }
  uint64_t ins[4]={0x0807060504030201ull,0,0,0}, outs[2];
  ext_dct8_eval(nullptr,outs,ins,0);
  printf("%016llx\n",(unsigned long long)outs[0]);
}
