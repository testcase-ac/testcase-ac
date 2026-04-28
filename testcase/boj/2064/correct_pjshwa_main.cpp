#include <cstdio>
typedef long long ll;
using namespace std;

int main() {
  ll n, p[4], c[4], pi, ci, xi;
  int xb = 0;
  scanf("%lld\n", &n);

  scanf("%lld.%lld.%lld.%lld\n", p, p + 1, p + 2, p + 3);
  pi = (1LL << 24) * p[0] + (1LL << 16) * p[1] + (1LL << 8) * p[2] + p[3];

  for (int i = 1; i < n; i++) {
    scanf("%lld.%lld.%lld.%lld\n", c, c + 1, c + 2, c + 3);
    ci = (1LL << 24) * c[0] + (1LL << 16) * c[1] + (1LL << 8) * c[2] + c[3];
    xi = pi ^ ci;
    for (int j = 0; j < 32; j++) {
      if (((1LL << j) & xi) && j + 1 > xb) xb = j + 1;
    }
  }

  ll mask = ((1LL << 32) - (1LL << xb));
  ll mip = pi & mask;

  for (int i = 3; i > 0; i--) {
    printf("%lld.", mip / (1LL << (8 * i)));
    mip %= (1LL << (8 * i));
  }
  printf("%lld\n", mip);

  for (int i = 3; i > 0; i--) {
    printf("%lld.", mask / (1LL << (8 * i)));
    mask %= (1LL << (8 * i));
  }
  printf("%lld\n", mask);
}
