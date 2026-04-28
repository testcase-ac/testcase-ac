#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
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
  int n; string s;
  cin >> n >> s;

  int wc = 0, ec = 0;
  for (int i = 0; i < n; i++) if (s[i] == 'W') wc++;

  ll ans = 0;
  for (int i = n - 1; i >= 0; i--) {
    if (s[i] == 'W') wc--;
    if (s[i] == 'E') ec++;
    if (s[i] == 'H') {
      ll cur = (lpow(2, ec, MOD) + MOD - 1 - ec) % MOD;
      cur = (cur * wc) % MOD;
      ans = (ans + cur) % MOD;
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
