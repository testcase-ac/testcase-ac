#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 400, MOD = 1e9 + 9;
const int dx[] = {1, 2, 2, 1, -1, -2, -2, -1}, dy[] = {2, 1, -1, -2, -2, -1, 1, 2};
int dp[MAXN][MAXN];
bool vis[MAXN][MAXN];

void solve() {
  int r, c; cin >> r >> c;

  queue<tuple<int, int, int>> q;
  q.emplace(0, 0, 0); dp[0][0] = 1;
  while (!q.empty()) {
    auto [x, y, d] = q.front(); q.pop();
    if (x == r - 1 && y == c - 1) {
      cout << d << ' ' << dp[x][y] << '\n';
      return;
    }
    for (int k = 0; k < 8; k++) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
      dp[nx][ny] = (dp[nx][ny] + dp[x][y]) % MOD;
      if (!vis[nx][ny]) {
        vis[nx][ny] = true;
        q.emplace(nx, ny, d + 1);
      }
    }
  }

  cout << "None\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
