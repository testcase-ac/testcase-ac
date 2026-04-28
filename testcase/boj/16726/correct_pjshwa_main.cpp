#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50, MAXC = 2500;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

vector<int> graph[MAXC];
char board[MAXN + 1][MAXN + 1];
int C[MAXC];
bool vis[MAXC];

bool dfs(int v) {
  for (int u : graph[v]) {
    if (vis[u]) continue;
    vis[u] = true;
    if (C[u] == -1 || dfs(C[u])) {
      C[u] = v;
      return true;
    }
  }
  return false;
}

void solve() {
  int N, M; cin >> N >> M;

  int total = 0;
  for (int i = 0; i < N; ++i) {
    cin >> board[i];
    for (int j = 0; j < M; ++j) {
      if (board[i][j] == '.') ++total;
    }
  }

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if ((i + j) % 2 || board[i][j] == 'X') continue;
    for (int k = 0; k < 4; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M || board[ni][nj] == 'X') continue;
      graph[i * M + j].push_back(ni * M + nj);
    }
  }

  int match = 0;
  memset(C, -1, sizeof C);
  for (int i = 0; i < N * M; ++i) {
    memset(vis, false, sizeof vis);
    if (dfs(i)) ++match;
  }

  cout << total - match << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
