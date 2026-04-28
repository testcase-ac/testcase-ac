#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

void solve() {
  ll a, b, c;
  cin >> a >> b >> c;
  cout << (ll)lpow(a, b, c) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
