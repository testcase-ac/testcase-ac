#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 8;
int board[MAX][MAX], oboard[MAX][MAX];
int n, m;

void init() {
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) board[i][j] = oboard[i][j];
}

int bfs() {
  queue<pair<int, int>> q;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == 2) q.push({i, j});
  }

  while (!q.empty()) {
    auto [i, j] = q.front();
    q.pop();

    board[i][j] = 2;
    if (i > 0 && board[i - 1][j] == 0) board[i - 1][j] = 2, q.push({i - 1, j});
    if (i < n - 1 && board[i + 1][j] == 0) board[i + 1][j] = 2, q.push({i + 1, j});
    if (j > 0 && board[i][j - 1] == 0) board[i][j - 1] = 2, q.push({i, j - 1});
    if (j < m - 1 && board[i][j + 1] == 0) board[i][j + 1] = 2, q.push({i, j + 1});
  }

  int ans = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == 0) ans++;
  }
  return ans;
}

int main() {
  fast_io();

  cin >> n >> m;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> oboard[i][j];

  int mval = 0;
  for (int u = 0; u < n * m; u++) for (int v = u + 1; v < n * m; v++) for (int w = v + 1; w < n * m; w++) {
    if (oboard[u / m][u % m] == 0 && oboard[v / m][v % m] == 0 && oboard[w / m][w % m] == 0) {
      init();
      board[u / m][u % m] = 1;
      board[v / m][v % m] = 1;
      board[w / m][w % m] = 1;
      mval = max(mval, bfs());
    }
  }
  cout << mval << '\n';
}
