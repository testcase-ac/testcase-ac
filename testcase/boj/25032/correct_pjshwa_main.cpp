#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

#include <sys/resource.h>


void enlarge_stack() {
  struct rlimit lim;
  getrlimit(RLIMIT_STACK, &lim);
  lim.rlim_cur = lim.rlim_max;
  setrlimit(RLIMIT_STACK, &lim);
}

const int MAX = 400;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
char board[MAX + 1][MAX + 1];
int b2r[MAX][MAX], b3r[MAX][MAX], n, m;
int b3b[4 *MAX][4 *MAX], b3z[4 *MAX][4 *MAX], sz;
bool vis[4 *MAX][4 *MAX];

void dfs1(int i, int j, int lim) {
  vis[i][j] = 1;
  sz++;
  for (int k = 0; k < 4; k++) {
    int nx = i + dx[k], ny = j + dy[k];
    if (nx < 0 || nx >= lim * n || ny < 0 || ny >= lim * m) continue;
    if (b3b[i][j] == b3b[nx][ny] && !vis[nx][ny]) dfs1(nx, ny, lim);
  }
}

void dfs2(int i, int j, int sz, int lim) {
  b3z[i][j] = sz;
  for (int k = 0; k < 4; k++) {
    int nx = i + dx[k], ny = j + dy[k];
    if (nx < 0 || nx >= lim * n || ny < 0 || ny >= lim * m) continue;
    if (b3b[i][j] == b3b[nx][ny] && b3z[nx][ny] == -1) dfs2(nx, ny, sz, lim);
  }
}

void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  memset(b3b, -1, sizeof(b3b));
  for (int i = 0; i < 3 * n; i++) for (int j = 0; j < 3 * m; j++) b3b[i][j] = board[i % n][j % m] == 'W';

  memset(vis, 0, sizeof(vis));
  memset(b3z, -1, sizeof(b3z));
  for (int i = 0; i < 3 * n; i++) for (int j = 0; j < 3 * m; j++) {
    if (vis[i][j]) continue;
    sz = 0;
    dfs1(i, j, 3);
    dfs2(i, j, sz, 3);
  }

  for (int i = 0; i < 3 * n; i++) {
    for (int j = 0; j < 3 * m; j++) cout << b3z[i][j] << " ";
    cout << endl;
  }

  for (int i = 0; i < 3 * n; i++) for (int j = 0; j < 3 * m; j++) {
    b2r[i % n][j % m] = max(b2r[i % n][j % m], b3z[i][j]);
  }
  
  memset(b3b, -1, sizeof(b3b));
  for (int i = 0; i < 4 *n; i++) for (int j = 0; j < 4 *m; j++) b3b[i][j] = board[i % n][j % m] == 'W';

  memset(vis, 0, sizeof(vis));
  memset(b3z, -1, sizeof(b3z));
  for (int i = 0; i < 4 *n; i++) for (int j = 0; j < 4 *m; j++) {
    if (vis[i][j]) continue;
    sz = 0;
    dfs1(i, j, 4);
    dfs2(i, j, sz, 4);
  }

  // for (int i = 0; i < 4 *n; i++) {
  //   for (int j = 0; j < 4 *m; j++) cout << b3z[i][j] << " ";
  //   cout << endl;
  // }

  for (int i = 0; i < 4 *n; i++) for (int j = 0; j < 4 *m; j++) {
    b3r[i % n][j % m] = max(b3r[i % n][j % m], b3z[i][j]);
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (b2r[i][j] == b3r[i][j]) cout << b2r[i][j] << ' ';
      else cout << "-1 ";
    }
    cout << '\n';
  }

}

int main() {
  fast_io();
  enlarge_stack();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
