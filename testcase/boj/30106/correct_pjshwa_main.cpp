#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 500;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
int parent[MAX * MAX], A[MAX][MAX];

int Find(int x) {
  if (parent[x] == x) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

void solve() {
  int N, M, K; cin >> N >> M >> K;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> A[i][j];

  iota(parent, parent + MAX * MAX, 0);
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    for (int k = 0; k < 4; ++k) {
      int nx = i + dx[k], ny = j + dy[k];
      if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
      if (abs(A[i][j] - A[nx][ny]) > K) continue;
      Union(i * M + j, nx * M + ny);
    }
  }

  set<int> U;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) U.insert(Find(i * M + j));
  cout << U.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
