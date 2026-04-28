#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
const int mov[4][6] = {
  {5, 4, 2, 3, 0, 1},
  {4, 5, 2, 3, 1, 0},
	{3, 2, 0, 1, 4, 5},
  {2, 3, 1, 0, 4, 5}
};
char board[MAX + 1][MAX + 1];
bool vis[MAX][MAX][6];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  int si, sj;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == 'D') si = i, sj = j, board[i][j] = '.';
  }

  queue<tuple<int, int, int, int>> q;
  q.push({si, sj, 0, 0});
  vis[si][sj][0] = true;

  while (!q.empty()) {
    auto& [i, j, d, c] = q.front();
    q.pop();

    if (board[i][j] == 'R') return cout << c << '\n', void();

    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || nj < 0 || ni >= n || nj >= m) continue;
      if (board[ni][nj] == '#') continue;

      int x = mov[k][d];
      if (board[ni][nj] == 'R' && x != 0) continue;
      if (vis[ni][nj][x]) continue;

      vis[ni][nj][x] = true;
      q.push({ni, nj, x, c + 1});
    }
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
