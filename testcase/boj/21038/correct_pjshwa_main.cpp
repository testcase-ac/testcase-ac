#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

void solve() {
  ll N, M, K;
  cin >> N >> M >> K;

  ll ly = 0, lc = 0, ans = 1;
  while (K--) {
    ll y, c;
    cin >> y >> c;

    if (lc == 0) ans = (ans * lpow(N - 1, y - ly - 1, MOD));
    else {
      ll d = y - ly;
      if (d & 1) {
        ll u = (lpow(N - 1, y - ly, MOD) + 1) * lpow(N, MOD - 2, MOD) % MOD;
        if (lc == c) u = (u + MOD - 1) % MOD;
        ans = (ans * u) % MOD;
      }
      else {
        ll u = (lpow(N - 1, y - ly, MOD) - 1 + MOD) * lpow(N, MOD - 2, MOD) % MOD;
        if (lc == c) u = (u + 1) % MOD;
        ans = (ans * u) % MOD;
      }
    }
    ly = y, lc = c;
  }
  ans = ans * lpow(N - 1, M - ly, MOD) % MOD;

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
