#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 80;
const int dx[6] = {1, 0, -1, -1, 0, 1};
const int dy[6] = {-1, -1, -1, 1, 1, 1};
char board[MAXN + 1][MAXN + 1];
vector<int> adj[MAXN * MAXN];
int ma[MAXN * MAXN], mb[MAXN * MAXN];
bool vis[MAXN * MAXN];

bool dfs(int a) {
  vis[a] = true;
  for (int b : adj[a]) {
    if (mb[b] == -1 || (!vis[mb[b]] && dfs(mb[b]))) {
      ma[a] = b; mb[b] = a;
      return true;
    }
  }
  return false;
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    adj[i * M + j].clear();
  }

  int tot = 0;
  for (int i = 0; i < N; ++i) {
    cin >> board[i];
    for (int j = 0; j < M; ++j) tot += board[i][j] != 'x';
  }

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; j += 2) {
    if (board[i][j] == 'x') continue;
    for (int k = 0; k < 6; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M || board[ni][nj] == 'x') continue;
      adj[i * M + j].push_back(ni * M + nj);
    }
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; j += 2) {
    int u = i * M + j;
    if (ma[u] != -1) continue;
    fill(vis, vis + N * M, false);
    if (dfs(u)) ++match;
  }
  cout << tot - match << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
