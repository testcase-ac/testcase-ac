#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int level[MAX], parent[MAX][21];
ll P[MAX + 10];

int lca(int x, int y) {
  if (level[x] < level[y]) swap(x, y);
  int diff = level[x] - level[y];

  for (int i = 0; diff; i++) {
    if (diff % 2) x = parent[x][i];
    diff /= 2;
  }

  // level[x] = level[y] from now on.
  if (x != y) {
    for (int i = 20; i >= 0; i--) {
      if (!parent[x][i] || parent[x][i] == parent[y][i]) continue;

      x = parent[x][i];
      y = parent[y][i];
    }

    x = parent[x][0];
  }
  return x;
}

int dist(int x, int y) {
  return level[x] + level[y] - (2 * level[lca(x, y)]);
}

void solve() {
  int N, M, T; cin >> N >> M >> T;
  vector<vector<int>> A(N - 1, vector<int>(M));
  vector<vector<int>> B(N, vector<int>(M - 1));

  for (int i = 0; i < N - 1; i++) for (int j = 0; j < M; j++) cin >> A[i][j];
  for (int i = 0; i < N; i++) for (int j = 0; j < M - 1; j++) cin >> B[i][j];

  function<void(int, int, int, int, int)> dfs = [&](int i, int j, int pi, int pj, int l) {
    int v = i * M + j;
    level[v] = l;
    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (ni == pi && nj == pj) continue;

      if (k == 0 && A[i][j] == 1) continue;
      if (k == 1 && B[i][j] == 1) continue;
      if (k == 2 && A[i - 1][j] == 1) continue;
      if (k == 3 && B[i][j - 1] == 1) continue;

      int u = ni * M + nj;
      parent[u][0] = v;
      dfs(ni, nj, i, j, l + 1);
    }
  };

  dfs(0, 0, -1, -1, 0);
  for (int j = 0; j < 20; j++) for (int i = 1; i < N * M; i++) {
    if (parent[i][j]) parent[i][j + 1] = parent[parent[i][j]][j];
  }

  int K; cin >> K;
  while (K--) {
    int s, e, a, b, c, d, v; cin >> s >> e >> a >> b >> c >> d >> v;
    int m = dist(a * M + b, c * M + d) + 1;
    v *= m;
    P[s] += v; P[e + 1] -= v;
  }

  ll run = 0;
  for (int i = 1; i <= T; i++) {
    run += P[i];
    cout << run << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
