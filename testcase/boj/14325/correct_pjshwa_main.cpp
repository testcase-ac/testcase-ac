#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int board[MAX][MAX];
int parent[MAX * MAX], usz[MAX * MAX];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x == y) return;

  parent[y] = x;
  usz[x] += usz[y];
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N, M;
  cin >> N >> M;

  priority_queue<tii, vector<tii>, greater<tii>> pq;
  map<int, int> csz;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    cin >> board[i][j];
    pq.push({board[i][j], i, j});

    parent[i * M + j] = i * M + j;
    usz[i * M + j] = 1;
    csz[i * M + j] = board[i][j];
  }

  for (int i = 0; i < N; i++) Union(0, i * M), Union(0, i * M + M - 1);
  for (int j = 0; j < M; j++) Union(0, j), Union(0, (N - 1) * M + j);

  int ans = 0;
  while (!pq.empty()) {
    auto [v, i, j] = pq.top(); pq.pop();

    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (board[ni][nj] > v) continue;

      if (Find(ni * M + nj) == Find(i * M + j)) continue;

      if (Find(ni * M + nj) != Find(0)) {
        int diff = v - csz[Find(ni * M + nj)];
        ans += diff * usz[Find(ni * M + nj)];
      }
      Union(i * M + j, ni * M + nj);
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
