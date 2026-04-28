#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5, MOD = 1e9 + 7;

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
  int N;
  cin >> N;

  map<int, int> t;
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    t[x]++;
  }

  ll ans = 1;
  for (auto& [k, v] : t) ans = (ans * (v + 1)) % MOD;
  ans = (ans + MOD - 1) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
