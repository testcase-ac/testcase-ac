#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

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

__int128_t ra(__int128_t a, __int128_t pw, __int128_t mod) {
  if (pw == 0) return 1 % mod;
  if (pw == 1) return (a + 1) % mod;

  __int128_t tmp = ra(a, (pw - 1) >> 1, mod);
  __int128_t hpw = lpow(a, (pw + 1) >> 1, mod);
  __int128_t ret = (tmp * hpw) % mod;
  ret = (ret + tmp) % mod;
  if (pw % 2 == 0) ret = (ret + lpow(a, pw, mod)) % mod;

  return ret;
}

void solve() {
  ll m, a, c, x0, n, g;
  cin >> m >> a >> c >> x0 >> n >> g;

  __int128_t v = lpow(a, n, m);
  v = (v * x0) % m;
  __int128_t u = ra(a, n - 1, m);
  u = (u * c) % m;
  v = (v + u) % m;

  ll ans = v % g;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
