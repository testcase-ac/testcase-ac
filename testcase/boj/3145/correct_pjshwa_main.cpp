#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50;
const int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
const int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};
vector<int> adj[MAXN * MAXN];
char board[MAXN + 1][MAXN + 1];
int ma[MAXN * MAXN], mb[MAXN * MAXN];
bool vis[MAXN * MAXN];
int parent[MAXN * MAXN];

int Find(int x) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

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
  for (int i = 0; i < N; ++i) cin >> board[i];

  iota(parent, parent + N * M, 0);
  for (int i = 0; i < N; ++i) for (int j = M - 2; j >= 0; --j) {
    char cc = board[i][j], cp = board[i][j + 1];
    if (isupper(cc) && isupper(cp)) Union(i * M + j, i * M + j + 1);
  }

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (board[i][j] != 'x') continue;
    for (int k = 0; k < 8; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;

      char c = board[ni][nj];
      if (isupper(c)) adj[i * M + j].push_back(Find(ni * M + nj));
    }
  }

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (board[i][j] != 'x') continue;
    int u = i * M + j;
    sort(adj[u].begin(), adj[u].end());
    adj[u].erase(unique(adj[u].begin(), adj[u].end()), adj[u].end());
  }

  memset(ma, -1, sizeof(ma));
  memset(mb, -1, sizeof(mb));

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (board[i][j] != 'x') continue;
    int u = i * M + j;
    if (ma[u] != -1) continue;
    fill(vis, vis + N * M, false);
    dfs(u);
  }

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (board[i][j] != 'x') continue;
    cout << i + 1 << ' ' << j + 1 << ' ';

    int t = ma[i * M + j];
    assert(t != -1);

    int ti = t / M, tj = t % M;
    while (isupper(board[ti][tj])) cout << board[ti][tj++];
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
