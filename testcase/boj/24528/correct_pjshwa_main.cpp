#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6, MOD = 998244353;
ll d[27][MAX + 1];

void solve() {
  int n;
  cin >> n;

  d[26][0] = 1;
  for (int i = 1; i <= n; i++) {
    string s; int t;
    cin >> s >> t;

    int u = s[0] - 'a';
    for (int j = 0; j < 27; j++) {
      if (u == j) d[u][i] = (d[u][i] + d[j][i - 1]) % MOD;
      else {
        d[u][i] = (d[u][i] + t * d[j][i - 1]) % MOD;
        d[j][i] = d[j][i - 1];
      }
    }
  }

  ll ans = 0;
  for (int j = 0; j < 26; j++) ans = (ans + d[j][n]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
