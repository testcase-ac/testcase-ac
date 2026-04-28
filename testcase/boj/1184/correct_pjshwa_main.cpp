#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

const int MAX = 50;
int board[MAX + 1][MAX + 1], pf[MAX + 1][MAX + 1];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) cin >> board[i][j];
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
    pf[i][j] = pf[i - 1][j] + pf[i][j - 1] - pf[i - 1][j - 1] + board[i][j];
  }

  int ans = 0;
  map<int, int> v;
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
    v.clear();
    for (int dx = 1; dx <= n; dx++) for (int dy = 1; dy <= n; dy++) {
      if (i - dx < 0 || j - dy < 0) continue;
      int val = pf[i][j] - pf[i - dx][j] - pf[i][j - dy] + pf[i - dx][j - dy];
      v[val]++;
    }
    for (int dx = 1; dx <= n; dx++) for (int dy = 1; dy <= n; dy++) {
      if (i + dx > n || j + dy > n) continue;
      int val = pf[i + dx][j + dy] - pf[i][j + dy] - pf[i + dx][j] + pf[i][j];
      ans += v[val];
    }

    v.clear();
    for (int dx = 1; dx <= n; dx++) for (int dy = 1; dy <= n; dy++) {
      if (i - dx < 0 || j + dy > n) continue;
      int val = pf[i][j + dy] - pf[i - dx][j + dy] - pf[i][j] + pf[i - dx][j];
      v[val]++;
    }
    for (int dx = 1; dx <= n; dx++) for (int dy = 1; dy <= n; dy++) {
      if (i + dx > n || j - dy < 0) continue;
      int val = pf[i + dx][j] - pf[i][j] - pf[i + dx][j - dy] + pf[i][j - dy];
      ans += v[val];
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
