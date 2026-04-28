#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
char board[MAX + 1][MAX + 1];
int cdist[MAX + 1][MAX + 1];
vector<pii> graph[MAX + 1][MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == 'H') continue;
    int u = board[i][j] - '0';
    for (int k = 0; k < 4; k++) {
      int ni = i + u * dx[k], nj = j + u * dy[k];
      if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
      if (board[ni][nj] != 'H') graph[i][j].push_back({ni, nj});
    }
  }

  memset(cdist, -1, sizeof cdist);

  int ans = 0;
  queue<tii> q;
  q.push({0, 0, 1});
  cdist[0][0] = 1;

  while (!q.empty()) {
    auto [i, j, d] = q.front(); q.pop();

    if (d > 3000) return cout << "-1\n", void();
    ans = max(ans, d);

    for (auto [ni, nj] : graph[i][j]) {
      if (cdist[ni][nj] == -1 || cdist[ni][nj] < d + 1) {
        cdist[ni][nj] = d + 1;
        q.push({ni, nj, d + 1});
      }
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
