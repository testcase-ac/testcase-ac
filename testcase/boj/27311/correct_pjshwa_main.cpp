#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 10;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
char board[MAX + 1][MAX + 1];
bool vis[MAX + 1][MAX + 1];

void dfs(int i, int j) {
  vis[i][j] = true;
  for (int k = 0; k < 4; k++) {
    int ni = i + dx[k], nj = j + dy[k];
    if (ni < 0 || ni >= MAX || nj < 0 || nj >= MAX) continue;
    if (vis[ni][nj] || board[ni][nj] == '.') continue;
    dfs(ni, nj);
  }
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> board[i];

  memset(vis, 0, sizeof(vis));

  int cc = 0;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (vis[i][j] || board[i][j] == '.') continue;
    dfs(i, j);
    cc += 1;
  }
  if (cc != 1) return cout << "0\n", void();

  int maxx = -1, minx = MAX, maxy = -1, miny = MAX;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (board[i][j] == '.') continue;
    maxx = max(maxx, i);
    minx = min(minx, i);
    maxy = max(maxy, j);
    miny = min(miny, j);
  }

  int oc = 0;
  int maxx_o = -1, minx_o = MAX, maxy_o = -1, miny_o = MAX;
  for (int i = minx; i <= maxx; i++) for (int j = miny; j <= maxy; j++) {
    if (board[i][j] == '.') {
      oc += 1;
      maxx_o = max(maxx_o, i);
      minx_o = min(minx_o, i);
      maxy_o = max(maxy_o, j);
      miny_o = min(miny_o, j);
    }
  }
  if (oc == 0) return cout << "0\n", void();

  for (int i = minx_o; i <= maxx_o; i++) for (int j = miny_o; j <= maxy_o; j++) {
    if (board[i][j] == '.') continue;
    return cout << "0\n", void();
  }

  int ec = 0;
  if (minx_o == minx) ec += 1;
  if (maxx_o == maxx) ec += 1;
  if (miny_o == miny) ec += 1;
  if (maxy_o == maxy) ec += 1;

  if (ec == 2 && maxx - minx == maxy - miny && maxx_o - minx_o == maxy_o - miny_o) cout << "1\n";
  else cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
