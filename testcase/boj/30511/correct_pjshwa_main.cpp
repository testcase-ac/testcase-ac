#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
const int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
const int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
vector<int> adj[MAXN * MAXN];
int ma[MAXN * MAXN], mb[MAXN * MAXN];
bool vis[MAXN * MAXN];
char B[MAXN + 1][MAXN + 1];
vector<int> primes;

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
  for (int i = 0; i < N; ++i) cin >> B[i];

  auto oob = [&](int x, int y) {
    return x < 0 || x >= N || y < 0 || y >= M;
  };

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (B[i][j] != 'S') continue;

    for (int k = 0; k < 8; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (oob(ni, nj) || B[ni][nj] != 'G') continue;

      int mi1 = i + 2 * dx[k], mj1 = j + 2 * dy[k];
      int mi2 = i - dx[k], mj2 = j - dy[k], ok = 0;
      if (!oob(mi1, mj1) && B[mi1][mj1] == 'M') ok = 1;
      if (!oob(mi2, mj2) && B[mi2][mj2] == 'M') ok = 1;
      if (ok) adj[i * M + j].push_back(ni * M + nj);
    }
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    int u = i * M + j;
    if (B[i][j] != 'S' || ma[u] != -1) continue;
    fill(vis, vis + N * M, false);
    if (dfs(u)) ++match;
  }
  cout << match << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
