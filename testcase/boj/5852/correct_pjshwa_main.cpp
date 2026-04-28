#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50, INF = 1e9 + 7;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
char board[MAX + 1][MAX + 1];
int group[MAX + 1][MAX + 1];
bool vis[MAX + 1][MAX + 1];
int cost[16][16], d[1 << 16][16];
int N, M;

void dfs(int i, int j, int g) {
  group[i][j] = g;
  for (int k = 0; k < 4; k++) {
    int x = i + dx[k], y = j + dy[k];
    if (x < 0 || x >= N || y < 0 || y >= M) continue;
    if (board[x][y] == 'X' && group[x][y] == 0) dfs(x, y, g);
  }
}

void solve() {
  cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> board[i];

  int cg = 0;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (board[i][j] == 'X' && group[i][j] == 0) dfs(i, j, ++cg);
  }

  for (int g = 1; g <= cg; g++) {
    for (int tg = 1; tg <= cg; tg++) {
      if (g != tg) cost[g][tg] = INF;
    }

    queue<tuple<int, int, int>> q;
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
      if (group[i][j] == g) {
        q.push({i, j, 0});
        vis[i][j] = 1;
      }
    }

    while (!q.empty()) {
      auto [i, j, c] = q.front();
      q.pop();

      for (int k = 0; k < 4; k++) {
        int x = i + dx[k], y = j + dy[k];
        if (x < 0 || x >= N || y < 0 || y >= M) continue;
        if (vis[x][y]) continue;

        if (board[x][y] == 'S') {
          q.push({x, y, c + 1});
          vis[x][y] = 1;
        }
        else if (board[x][y] == 'X' && group[x][y] != g) {
          int tg = group[x][y];
          cost[g][tg] = min(cost[g][tg], c);
          vis[x][y] = 1;
        }
      }
    }

  }

  // Floyd-Warshall
  for (int k = 1; k <= cg; k++) for (int i = 1; i <= cg; i++) for (int j = 1; j <= cg; j++) {
    cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
  }

  // TSP
  for (int i = 1; i < (1 << cg); i++) for (int j = 1; j <= cg; j++) {
    if (__builtin_popcount(i) == 1 && (i & (1 << (j - 1)))) continue;
    d[i][j] = INF;
  }

  for (int i = 1; i < (1 << cg); i++) for (int j = 1; j <= cg; j++) {
    if (!(i & (1 << (j - 1)))) continue;

    for (int k = 1; k <= cg; k++) {
      if (j == k) continue;
      if (i & (1 << (k - 1))) continue;

      d[i | (1 << (k - 1))][k] = min(d[i | (1 << (k - 1))][k], d[i][j] + cost[j][k]);
    }
  }

  int ans = INF;
  for (int i = 1; i <= cg; i++) {
    ans = min(ans, d[(1 << cg) - 1][i]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
