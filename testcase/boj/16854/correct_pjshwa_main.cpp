#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000;
bool p[MAX][MAX];

void solve() {
  string s;
  cin >> s;
  int n = s.size();

  for (int i = 0; i < n - 1; i++) p[i][i + 1] = s[i] != s[i + 1];
  for (int diff = 2; diff < n; diff++) {
    for (int i = 0; i < n - diff; i++) {
      int j = i + diff;
      p[i][j] = (s[i] != s[j] && p[i + 1][j - 1]);
    }
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {

    int pf = 0;
    for (int j = i; j < n; j++) {
      if (s[j] == '(') pf++;
      else pf--;

      if (pf < 0) break;
      if (p[i][j]) ans++;
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
