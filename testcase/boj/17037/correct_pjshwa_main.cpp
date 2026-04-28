#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e3 + 10;
int dt[MAX][MAX];
int board[MAX][MAX];

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    dt[x1][y1]++;
    dt[x2][y2]++;
    dt[x1][y2]--;
    dt[x2][y1]--;
  }

  board[0][0] = dt[0][0];
  for (int i = 1; i < MAX; i++) board[i][0] = board[i - 1][0] + dt[i][0];
  for (int i = 1; i < MAX; i++) board[0][i] = board[0][i - 1] + dt[0][i];
  for (int i = 1; i < MAX; i++) for (int j = 1; j < MAX; j++) {
    board[i][j] = board[i - 1][j] + board[i][j - 1] - board[i - 1][j - 1] + dt[i][j];
  }

  int ans = 0;
  for (int i = 0; i < MAX; i++) for (int j = 0; j < MAX; j++) {
    if (board[i][j] == k) ans++;
  }

  cout << ans << '\n';
}
