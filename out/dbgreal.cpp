#include <cstdint>
#include <cstdio>
#include <array>
static constexpr std::array<int16_t, 64> kCoef = [] {
    std::array<int16_t, 64> t{};
    constexpr int rows[8][8] = {
        {181, 181, 181, 181, 181, 181, 181, 181},
        {126, 106, 71, 36, -36, -71, -106, -126},
        {118, 49, -49, -118, -118, -49, 49, 118},
        {102, -25, -95, -59, 59, 95, 25, -102},
        {91, -91, -91, 91, 91, -91, -91, 91},
        {71, -106, 36, 126, -126, -36, 106, -71},
        {49, -118, 118, -49, -49, 118, -118, 49},
        {36, -71, 106, -126, 126, -106, 71, -36},
    };
    for (int u = 0; u < 8; ++u)
        for (int x = 0; x < 8; ++x)
            t[u * 8 + x] = static_cast<int16_t>(rows[u][x]);
    return t;
}();
int main(){
  for(int u=0;u<2;++u){
    int32_t acc=0;
    for(int x=0;x<8;++x){
      const uint8_t s=static_cast<uint8_t>((0x0807060504030201ull >> (8*x)) & 0xFFu);
      acc += static_cast<int32_t>(kCoef[u*8+x]) * static_cast<int32_t>(s);
      printf("u%d x%d s=%d c=%d acc=%d\n",u,x,(int)s,(int)kCoef[u*8+x],acc);
    }
    printf("u%d final %04x\n",u,(uint16_t)acc);
  }
}
