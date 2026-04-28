#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int A[MAXN][MAXN];
int parent[MAXN * MAXN], indegree[MAXN * MAXN], H[MAXN * MAXN];
vector<int> adj[MAXN * MAXN];

int Find(int x) {
  if (parent[x] == x) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[x] = y;
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> A[i][j];

  iota(parent, parent + N * M, 0);
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) for (int k = 0; k < 4; ++k) {
    int ni = i + dx[k], nj = j + dy[k];
    if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
    if (A[ni][nj] == A[i][j]) Union(i * M + j, ni * M + nj);
  }
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) for (int k = 0; k < 4; ++k) {
    int ni = i + dx[k], nj = j + dy[k];
    if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
    if (A[ni][nj] > A[i][j]) {
      int x = Find(i * M + j), nx = Find(ni * M + nj);
      ++indegree[nx]; adj[x].push_back(nx);
    }
  }

  set<int> groups;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) groups.insert(Find(i * M + j));

  queue<int> Q;
  for (int x : groups) if (indegree[x] == 0) Q.push(x);

  int t = 0;
  while (!Q.empty()) {
    queue<int> nQ;

    while (!Q.empty()) {
      int x = Q.front(); Q.pop();
      H[x] = t;
      for (int nx : adj[x]) {
        if (--indegree[nx] == 0) nQ.push(nx);
      }
    }

    ++t;
    Q = nQ;
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) cout << H[Find(i * M + j)] << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
