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
  int N, a; cin >> N >> a;

  ll ans = lpow(N, a, MOD);
  ans = (ans * (N - 1)) % MOD;

  ll R = (N - 1) * lpow(N, MOD - 2, MOD) % MOD;
  ans = (ans * (lpow(R, a, MOD) - 1 + MOD)) % MOD;
  ans = (ans * lpow(R + MOD - 1, MOD - 2, MOD)) % MOD;

  ll add = N;
  add = (add * lpow(N - 1, a, MOD)) % MOD;
  ans = (ans + add) % MOD;

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
