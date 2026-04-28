#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 55;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
int n, m;
char board[MAX][MAX];
int cco[MAX][MAX], dist[3][MAX][MAX];
bool vis[MAX][MAX];

void mark(int si, int sj, int cc) {
  queue<pii> q;
  q.push({si, sj});
  cco[si][sj] = cc;

  while (!q.empty()) {
    auto [i, j] = q.front();
    q.pop();

    for (int k = 0; k < 4; ++k) {
      int ni = i + dx[k];
      int nj = j + dy[k];
      if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
      if (cco[ni][nj] == cc) continue;
      if (board[ni][nj] != 'X') continue;
      cco[ni][nj] = cc;
      q.push({ni, nj});
    }
  }
}

void print_board() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << cco[i][j];
    }
    cout << '\n';
  }
}

int d2se(int s, int e) {
  queue<tii> q;
  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    if (cco[i][j] == s) vis[i][j] = true, q.push({i, j, 0});
  }

  while (!q.empty()) {
    auto [i, j, c] = q.front();
    q.pop();

    if (cco[i][j] == e) return c - 1;

    for (int k = 0; k < 4; ++k) {
      int ni = i + dx[k];
      int nj = j + dy[k];
      if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
      if (vis[ni][nj]) continue;
      vis[ni][nj] = true;
      q.push({ni, nj, c + 1});
    }
  }
}

void mark_dfi(int s) {
  queue<tii> q;
  memset(vis, 0, sizeof(vis));
  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    if (cco[i][j] == s) vis[i][j] = true, q.push({i, j, 0});
  }

  while (!q.empty()) {
    auto [i, j, c] = q.front();
    q.pop();

    dist[s - 1][i][j] = c;

    for (int k = 0; k < 4; ++k) {
      int ni = i + dx[k];
      int nj = j + dy[k];
      if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
      if (vis[ni][nj]) continue;
      vis[ni][nj] = true;
      q.push({ni, nj, c + 1});
    }
  }
}

int main() {
  fast_io();

  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  int cc = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (!cco[i][j] && board[i][j] == 'X') mark(i, j, ++cc);
  }

  int d1 = d2se(1, 2), d2 = d2se(1, 3), d3 = d2se(2, 3);
  int ans = d1 + d2 + d3 - max({d1, d2, d3});

  mark_dfi(1);
  mark_dfi(2);
  mark_dfi(3);

  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (!cco[i][j]) {
      ans = min(ans, dist[0][i][j] + dist[1][i][j] + dist[2][i][j] - 2);
    }
  }

  cout << ans << '\n';
}
