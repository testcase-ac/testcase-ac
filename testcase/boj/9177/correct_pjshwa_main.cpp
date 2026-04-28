#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
bool d[MAX + 1][MAX + 1];

int tc;
void solve() {
  cout << "Data set " << ++tc << ": ";

  string S, T, U;
  cin >> S >> T >> U;

  int n = S.size(), m = T.size();
  memset(d, 0, sizeof d);
  d[0][0] = 1;
  for (int i = 0; i <= n; i++) for (int j = 0; j <= m; j++) {
    if (i && S[i - 1] == U[i + j - 1]) d[i][j] |= d[i - 1][j];
    if (j && T[j - 1] == U[i + j - 1]) d[i][j] |= d[i][j - 1];
  }

  if (d[n][m]) cout << "yes\n";
  else cout << "no\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
