#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int board[MAX][MAX], d[3][MAX][MAX], n;

int r(int type, int i, int j) {
  if (i == 1 || j == n) return 0;
  if (d[type][i][j] != -1) return d[type][i][j];

  int res = max(r(type, i + 1, j), r(type, i, j + 1));
  if (board[i][j] == type) {
    res = max(res, r((type + 1) % 3, i + 1, j) + 1);
    res = max(res, r((type + 1) % 3, i, j + 1) + 1);
  }
  return d[type][i][j] = res;
}

void solve() {
  cin >> n;
  for (int j = 0; j < n; j++) cin >> board[0][j];

  memset(d, -1, sizeof(d));
  cout << r(0, 0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
