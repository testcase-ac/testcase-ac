#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
vector<int> adj[MAXN * MAXN];
int ma[MAXN * MAXN], mb[MAXN * MAXN];
bool vis[MAXN * MAXN];
bool B[MAXN][MAXN];

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

int N, M;
void solve() {
  int K; cin >> K;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    adj[i * M + j].clear();
    B[i][j] = false;
  }

  while (K--) {
    int x, y; cin >> x >> y;
    B[x - 1][y - 1] = true;
  }

  auto oob = [&](int x, int y) {
    return x < 0 || x >= N || y < 0 || y >= M;
  };
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (B[i][j] || (i + j) % 2 == 0) continue;

    int u = i * M + j;
    for (int k = 0; k < 4; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (oob(ni, nj) || B[ni][nj]) continue;
      adj[u].push_back(ni * M + nj);
    }
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    int u = i * M + j;
    if (B[i][j] || (i + j) % 2 == 0) continue;
    fill(vis, vis + N * M, false);
    if (dfs(u)) ++match;
  }
  cout << match << '\n';
}

int main() {
  fast_io();

  while (cin >> N >> M) {
    if (N == 0 && M == 0) break;
    solve();
  }
}
