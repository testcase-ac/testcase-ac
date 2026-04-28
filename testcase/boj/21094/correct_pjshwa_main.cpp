#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

__int128_t lpow(__int128_t x, __int128_t y, __int128_t m) {
  __int128_t r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
__int128_t a[MAX + 1];
int main() {
  fast_io();

  int n;
  cin >> n;

  ll m = 1e18;
  m += 31;

  a[MAX] = 300;
  for (int i = MAX - 1; i >= 0; i--) a[i] = lpow(42, a[i + 1], m);
  
  cout << (ll)a[n];
}
