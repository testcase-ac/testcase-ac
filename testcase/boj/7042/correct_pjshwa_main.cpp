#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
int B[MAXN][MAXN], indeg[MAXN * MAXN], outdeg[MAXN * MAXN];
int parent[MAXN * MAXN];

int Find(int x) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x); y = Find(y);
  if (x != y) parent[x] = y;
}

void solve() {
  int M, N; cin >> M >> N;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> B[i][j];

  iota(parent, parent + N * M, 0);
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    for (int k = 0; k < 4; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (B[i][j] != B[ni][nj]) continue;
      Union(i * M + j, ni * M + nj);
    }
  }

  set<int> groups;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    int g = Find(i * M + j);
    groups.insert(g);
    for (int k = 0; k < 4; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (B[i][j] <= B[ni][nj]) continue;

      // (i, j) -> (ni, nj)
      int ng = Find(ni * M + nj);
      ++outdeg[g]; ++indeg[ng];
    }
  }

  int source_cnt = 0, sink_cnt = 0;
  for (int g : groups) {
    if (indeg[g] == 0 && outdeg[g] == 0) continue;
    if (indeg[g] == 0) ++source_cnt;
    if (outdeg[g] == 0) ++sink_cnt;
  }
  cout << max(source_cnt, sink_cnt) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
