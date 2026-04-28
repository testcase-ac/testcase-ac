#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
int board[MAX][MAX], oboard[MAX][MAX];
int n;

void rotate45() {
  for (int i = 0; i < n; i++) {
    board[i][n / 2] = oboard[i][i];
    board[i][n - 1 - i] = oboard[i][n / 2];
    board[n / 2][n - 1 - i] = oboard[i][n - 1 - i];
    board[n - 1 - i][n - 1 - i] = oboard[n / 2][n - 1 - i];
  }
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) oboard[i][j] = board[i][j];
}

void solve() {
  int d;
  cin >> n >> d;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> board[i][j];
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) oboard[i][j] = board[i][j];

  d = (d + 360) % 360;
  for (int i = 0; i < d / 45; i++) rotate45();

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cout << oboard[i][j] << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
