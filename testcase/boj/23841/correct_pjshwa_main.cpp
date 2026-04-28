#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
char board[MAX + 1][MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  for (int i = 0; i < n; i++) for (int j = 0; j < m / 2; j++) {
    if (board[i][j] == '.') board[i][j] = board[i][m - 1 - j];
    else board[i][m - 1 - j] = board[i][j];
  }

  for (int i = 0; i < n; i++) cout << board[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
