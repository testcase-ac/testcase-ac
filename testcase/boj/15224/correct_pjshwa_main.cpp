#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;

ll f(ll n) {
  if (n == 1) return 0;
  if (n % 2 == 0) return f(n / 2) + 1;
  else return f(n + 1) + 1;
}

// g(n) = f(1) + f(2) + ... + f(n)
ll g(ll n) {
  if (n <= 1) return 0;

  ll ret = 0;
  if (n & 1) ret = (ret + f(n)) % MOD;

  ll h = n / 2, S = g(h);
  ret = (ret + 2 * S) % MOD;
  ret = (ret + 3 * h) % MOD;
  ret = (ret - 2 + MOD) % MOD;
  return ret;
}

void solve() {
  ll L, R; cin >> L >> R;
  
  ll ans = (g(R) - g(L - 1) + MOD) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
