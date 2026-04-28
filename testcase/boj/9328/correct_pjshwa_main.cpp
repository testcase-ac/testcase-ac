#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
char board[MAX + 1][MAX + 1];
bool vis[MAX][MAX], opened[26];
queue<pii> doors[26];

void solve() {
  int n, m;
  string s;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  memset(vis, 0, sizeof(vis));
  memset(opened, 0, sizeof(opened));
  for (int i = 0; i < 26; i++) while (!doors[i].empty()) doors[i].pop();

  cin >> s;
  if (s != "0") for (char c : s) opened[c - 'a'] = 1;

  queue<pii> q;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
      if ('a' <= board[i][j] && board[i][j] <= 'z') {
        opened[board[i][j] - 'a'] = 1;
        vis[i][j] = 1, q.push({i, j});
      }
    }
  }
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
      if (board[i][j] == '.' || board[i][j] == '$') vis[i][j] = 1, q.push({i, j});
      if ('A' <= board[i][j] && board[i][j] <= 'Z') {
        if (opened[board[i][j] - 'A']) vis[i][j] = 1, q.push({i, j});
        else doors[board[i][j] - 'A'].push({i, j});
      }
    }
  }

  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i], ny = y + dy[i];
      if (nx < 0 || nx >= n || ny < 0 || ny >= m || board[nx][ny] == '*' || vis[nx][ny]) continue;

      if ('a' <= board[nx][ny] && board[nx][ny] <= 'z') {
        int key = board[nx][ny] - 'a';
        if (!opened[key]) {
          opened[key] = 1;
          while (!doors[key].empty()) {
            auto [x, y] = doors[key].front();
            doors[key].pop();
            vis[x][y] = 1, q.push({x, y});
          }
        }
        vis[nx][ny] = 1, q.push({nx, ny});
      }
      else if ('A' <= board[nx][ny] && board[nx][ny] <= 'Z') {
        int door = board[nx][ny] - 'A';
        if (opened[door]) vis[nx][ny] = 1, q.push({nx, ny});
        else doors[door].push({nx, ny});
      }
      else vis[nx][ny] = 1, q.push({nx, ny});
    }
  }

  int ans = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (vis[i][j] && board[i][j] == '$') ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
