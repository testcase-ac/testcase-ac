#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int A[MAX][MAX], vis[MAX][MAX];
int N, M;

void dfs(int i, int j, int cc) {
  vis[i][j] = cc;

  for (int k = 0; k < 4; k++) {
    int ni = i + dx[k], nj = j + dy[k];
    if (ni < 0) ni = N - 1;
    if (nj < 0) nj = M - 1;
    if (ni >= N) ni = 0;
    if (nj >= M) nj = 0;

    if (vis[ni][nj] || A[ni][nj]) continue;
    dfs(ni, nj, cc);
  }
}

void solve() {
  cin >> N >> M;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> A[i][j];

  int cc = 0;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (!vis[i][j] && !A[i][j]) dfs(i, j, ++cc);
  }
  cout << cc << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
