#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 500;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int A[MAX][MAX];
int parent[MAX * MAX], usz[MAX * MAX];
set<int> adj[MAX * MAX];

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
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> A[i][j];
  iota(parent, parent + N * M, 0);
  fill(usz, usz + N * M, 1);

  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;

      if (A[i][j] == A[ni][nj]) Union(i * M + j, ni * M + nj);
    }
  }

  set<int> groups;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    int g = Find(i * M + j);
    groups.insert(g);

    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;

      int ng = Find(ni * M + nj);
      if (g == ng) continue;

      adj[g].insert(ng);
    }
  }

  int ans = 0;
  for (int g : groups) {
    map<int, int> t;
    for (int ng : adj[g]) {
      int ni = ng / M, nj = ng % M;
      t[A[ni][nj]] += usz[ng];
    }

    int maxv = 0;
    for (auto [_, v] : t) maxv = max(maxv, v);
    ans = max(ans, maxv + usz[g]);
  }
  cout << ans << '\n';
}

// 1. TC 간 전역 변수 초기화
// 2. int overflow 체크
// 3. edge case 체크
// 4. 자주 하는 실수
//   - long long에 sqrt() 사용
//   - multiset::count() 사용
int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
