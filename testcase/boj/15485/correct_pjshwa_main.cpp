#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

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

const int MOD = 1e9 + 7;

void solve() {
  string s;
  cin >> s;
  int n = s.size();
  ll acur = 0, apfv = 0, ccur = 0, ans = 0;
  for (int i = 0; i < n; i++) if (s[i] == 'c') ccur++;
  for (int i = 0; i < n; i++) {
    if (s[i] == 'a') acur++;
    if (s[i] == 'c') ccur--;
    if (s[i] == 'b') {
      ll aadd = lpow(2, acur, MOD) + MOD - 1;
      ll cadd = lpow(2, ccur, MOD) + MOD - 1;
      ans = (ans + (apfv + aadd) * cadd) % MOD;
      apfv = (2 * apfv + aadd) % MOD;
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
