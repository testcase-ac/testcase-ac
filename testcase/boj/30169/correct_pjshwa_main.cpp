#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

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
  ll x, n; cin >> x >> n;

  vector<int> p_factors;
  for (int i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      p_factors.push_back(i);
      while (x % i == 0) x /= i;
    }
  }
  if (x > 1) p_factors.push_back(x);

  ll ans = 1;
  for (int p : p_factors) {
    __int128_t pw = p;
    while (pw <= n) {
      ll pw_cnt = n / pw;
      ans = (ans * lpow(p, pw_cnt, MOD)) % MOD;
      pw *= p;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
