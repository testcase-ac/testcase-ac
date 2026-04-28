#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
int board[MAX][MAX];
bool vis[MAX][MAX];

void solve() {
  int n, m;
  cin >> m >> n;

  queue<tii> q;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    cin >> board[i][j];
    if (board[i][j] == 1) {
      q.push({i, j, 0});
      vis[i][j] = true;
    }
  }

  int mdist = 0;
  while (!q.empty()) {
    auto [i, j, c] = q.front();
    q.pop();

    mdist = max(mdist, c);

    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= n || nj < 0 || nj >= m || vis[ni][nj]) continue;
      if (board[ni][nj] == -1) continue;
      vis[ni][nj] = true;
      q.push({ni, nj, c + 1});
    }
  }

  bool able = true;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] != -1 && !vis[i][j]) {
      able = false;
      break;
    }
  }

  if (able) cout << mdist << '\n';
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
//   cin >> t;
  while (t--) solve();
}
