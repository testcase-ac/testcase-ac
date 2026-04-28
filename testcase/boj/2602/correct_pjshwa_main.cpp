#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int d[2][20][100];

void solve() {
  string s, a, b;
  cin >> s >> a >> b;
  int u = s.size(), n = a.size();

  for (int i = 0; i < n; i++) {
    if (a[i] == s[0]) d[0][0][i] = 1;
    if (b[i] == s[0]) d[1][0][i] = 1;
  }

  for (int i = 0; i < n; i++) for (int j = 1; j < u; j++) {
    if (a[i] == s[j]) {
      for (int k = 0; k < i; k++) d[0][j][i] += d[1][j - 1][k];
    }
    if (b[i] == s[j]) {
      for (int k = 0; k < i; k++) d[1][j][i] += d[0][j - 1][k];
    }
  }

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ans += d[0][u - 1][i];
    ans += d[1][u - 1][i];
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
