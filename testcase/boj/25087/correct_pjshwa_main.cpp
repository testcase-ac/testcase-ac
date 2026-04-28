#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 200;
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
char board[MAX + 1][MAX + 1];
bool vis[2 * MAX + 1][2 * MAX + 1];
char ptr[2 * MAX + 1][2 * MAX + 1];
int R, C;

void dfs1(int i, int j) {
  vis[i][j] = 1;

  for (int k = 0; k < 4; k++) {
    int ni = i + dx[k], nj = j + dy[k];
    if (ni < 0 || ni >= R || nj < 0 || nj >= C) continue;
    if (vis[ni][nj] || board[ni][nj] == '#') continue;

    if (k == 0) {
      ptr[2 * i][2 * j] = 'N';
      ptr[2 * i - 1][2 * j + 1] = 'S';
    }
    if (k == 1) {
      ptr[2 * i][2 * j + 1] = 'E';
      ptr[2 * i + 1][2 * j + 2] = 'W';
    }
    if (k == 2) {
      ptr[2 * i + 1][2 * j + 1] = 'S';
      ptr[2 * i + 2][2 * j] = 'N';
    }
    if (k == 3) {
      ptr[2 * i + 1][2 * j] = 'W';
      ptr[2 * i][2 * j - 1] = 'E';
    }
    dfs1(ni, nj);
  }
}

void dfs2(int i, int j) {
  if (vis[i][j]) return;
  vis[i][j] = 1;

  cout << ptr[i][j];
  if (ptr[i][j] == 'E') dfs2(i, j + 1);
  if (ptr[i][j] == 'S') dfs2(i + 1, j);
  if (ptr[i][j] == 'W') dfs2(i, j - 1);
  if (ptr[i][j] == 'N') dfs2(i - 1, j);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  cin >> R >> C;
  for (int i = 0; i < R; i++) cin >> board[i];

  memset(vis, 0, sizeof(vis));
  queue<pii> q;
  q.emplace(0, 0);
  vis[0][0] = true;

  while (!q.empty()) {
    auto [x, y] = q.front(); q.pop();

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i], ny = y + dy[i];
      if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
      if (vis[nx][ny] || board[nx][ny] == '#') continue;
      vis[nx][ny] = true;
      q.emplace(nx, ny);
    }
  }

  for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) {
    if (board[i][j] == '*') {
      if (!vis[i][j]) return cout << "IMPOSSIBLE\n", void();

      ptr[2 * i][2 * j] = 'E';
      ptr[2 * i][2 * j + 1] = 'S';
      ptr[2 * i + 1][2 * j + 1] = 'W';
      ptr[2 * i + 1][2 * j] = 'N';
    }
  }

  memset(vis, 0, sizeof(vis));
  dfs1(0, 0);
  memset(vis, 0, sizeof(vis));
  dfs2(0, 0);
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
