#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
const int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1}, dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int board[MAX + 1][MAX + 1], cdist[MAX + 1][MAX + 1];

void solve() {
  int n, m, x, y;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> board[i][j];
  cin >> x >> y;

  priority_queue<tii, vector<tii>, greater<tii>> pq;
  cdist[x][y] = board[x][y];
  pq.push({cdist[x][y], x, y});

  while (!pq.empty()) {
    auto [wi, xi, yi] = pq.top();
    pq.pop();

    if (wi > cdist[xi][yi]) continue;
    cdist[xi][yi] = wi;

    for (int k = 0; k < 8; k++) {
      int nx = xi + dx[k], ny = yi + dy[k];
      if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
      // if (board[nx][ny] > 0) continue;

      int nw = max(board[nx][ny], wi);
      if (cdist[nx][ny] > nw) {
        cdist[nx][ny] = nw;
        pq.push({cdist[nx][ny], nx, ny});
      }
    }
  }

  ll ans = 0;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) ans += cdist[i][j];
  cout << -ans << '\n';
}

int main() {
  fast_io();
  
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
