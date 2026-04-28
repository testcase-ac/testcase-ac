#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 300;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int b[MAX][MAX], nb[MAX][MAX];
bool vis[MAX][MAX];
int N, M;

void dfs(int i, int j) {
  vis[i][j] = 1;
  for (int k = 0; k < 4; k++) {
    int nx = i + dx[k], ny = j + dy[k];
    if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
    if (b[nx][ny] > 0 && !vis[nx][ny]) dfs(nx, ny);
  }
}

void solve() {
  cin >> N >> M;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> b[i][j];

  for (int t = 1;; t++) {
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
      int nz = 0;
      for (int k = 0; k < 4; k++) {
        int nx = i + dx[k], ny = j + dy[k];
        if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
        if (b[nx][ny] == 0) nz++;
      }
      nb[i][j] = max(0, b[i][j] - nz);
    }
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) b[i][j] = nb[i][j];

    int cc = 0;
    memset(vis, 0, sizeof vis);
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
      if (b[i][j] > 0 && !vis[i][j]) {
        cc++;
        dfs(i, j);
      }
    }

    if (cc == 0) break;
    if (cc > 1) return cout << t << '\n', void();
  }

  cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
