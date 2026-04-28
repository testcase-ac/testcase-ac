#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
char board[MAX + 1][MAX + 1];
int parent[MAX * MAX], usz[MAX * MAX];
int maxx[MAX * MAX], maxy[MAX * MAX], minx[MAX * MAX], miny[MAX * MAX];

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

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> board[i];

  iota(parent, parent + N * M, 0);
  fill(usz, usz + N * M, 1);
  fill(maxx, maxx + N * M, -INF);
  fill(maxy, maxy + N * M, -INF);
  fill(minx, minx + N * M, INF);
  fill(miny, miny + N * M, INF);

  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (board[ni][nj] != board[i][j]) continue;
      Union(i * M + j, ni * M + nj);
    }
  }

  set<int> groups;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    int g = Find(i * M + j);
    groups.insert(g);

    maxx[g] = max(maxx[g], i);
    maxy[g] = max(maxy[g], j);
    minx[g] = min(minx[g], i);
    miny[g] = min(miny[g], j);
  }

  for (int g : groups) {
    int area = (maxx[g] - minx[g] + 1) * (maxy[g] - miny[g] + 1);
    if (area != usz[g]) return cout << "BaboBabo\n", void();
  }
  cout << "dd\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
