#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
ll board[MAX][MAX], d[MAX][MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> board[i][j];

  d[0][0] = 1;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    if (board[i][j] == 0) continue;
    if (i + board[i][j] < n) d[i + board[i][j]][j] += d[i][j];
    if (j + board[i][j] < n) d[i][j + board[i][j]] += d[i][j];
  }

  cout << d[n - 1][n - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
