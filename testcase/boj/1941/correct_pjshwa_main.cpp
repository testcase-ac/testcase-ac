#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAX = 5;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
char board[MAX + 1][MAX + 1];
bool vis[MAX][MAX], mark[MAX][MAX];
vector<int> current;
int n = 5, ans, yc, sc;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void dfs(int i, int j) {
  vis[i][j] = 1;
  board[i][j] == 'S' ? sc++ : yc++;
  for (int k = 0; k < 4; k++) {
    int nx = i + dx[k], ny = j + dy[k];
    if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
    if (!mark[nx][ny] || vis[nx][ny]) continue;
    dfs(nx, ny);
  }
}

void combination(int idx, int cnt) {
  if (cnt == 0) {
    yc = sc = 0;
    memset(vis, 0, sizeof(vis));
    dfs(current[0] / n, current[0] % n);
    if (sc + yc == 7 && sc > yc) ans++;
    return;
  }

  for (int i = idx; i < 25; i++) {
    current.push_back(i);
    mark[i / n][i % n] = 1;
    combination(i + 1, cnt - 1);
    mark[i / n][i % n] = 0;
    current.pop_back();
  }
}

void solve() {
  for (int i = 0; i < n; i++) cin >> board[i];
  ans = 0;
  combination(0, 7);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
