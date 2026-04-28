#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int A[MAX][MAX], vis[MAX][MAX];
int N, cnt;

void dfs(int i, int j) {
  vis[i][j] = 1; cnt++;
  for (int k = 0; k < 4; k++) {
    int x = i + dx[k], y = j + dy[k];
    if (x < 0 || x >= N || y < 0 || y >= N) continue;
    if (vis[x][y] || A[x][y] == 1) continue;
    dfs(x, y);
  }
}

void solve() {
  int M, K; cin >> N >> M >> K;
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cin >> A[i][j];

  int u = 0;
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    if (vis[i][j] || A[i][j]) continue;

    cnt = 0;
    dfs(i, j);
    u += (cnt - 1) / K + 1;
  }

  if (0 < u && u <= M) cout << "POSSIBLE\n" << M - u << '\n';
  else cout << "IMPOSSIBLE\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
