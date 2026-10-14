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
  uint64_t in=1;
  for(int u=0;u<4;++u){
    int32_t acc=0;
    for(int x=0;x<8;++x){
      uint8_t s=(in>>(8*x))&0xFF;
      acc += kCoef[u*8+x]*s;
    }
    printf("u=%d acc=%d %04x\n",u,acc,(uint16_t)acc);
  }
}
