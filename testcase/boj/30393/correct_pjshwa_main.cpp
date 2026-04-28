#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 998244353;

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
  int N, M; cin >> N >> M;

  vector<ll> A(N); ll ans = 0, sum = 0;
  for (ll& x : A) {
    cin >> x;
    ll c = (x * (x - 1) / 2) % MOD;
    ans = (ans + c) % MOD;
    sum += x;
  }

  ans = (ans * M) % MOD;
  ans = (ans * (M - 1)) % MOD;
  ans = (ans * lpow(sum, MOD - 2, MOD)) % MOD;
  ans = (ans * lpow(sum - 1, MOD - 2, MOD)) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
