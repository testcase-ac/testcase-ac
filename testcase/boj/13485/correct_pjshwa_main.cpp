#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
char board[10][MAX + 1];
bool vis[10][MAX];
pii from[10][MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < 10; i++) {
    cin >> board[i];
    for (int j = 0; j < n; j++) from[i][j] = {-1, -1};
  }

  queue<pii> q;
  q.push({9, 0});
  vis[9][0] = true;
  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();

    if (y == n - 1) {
      // exit routine
      stack<pii> traj;
      int xi = x, yi = y;
      while (from[xi][yi].first != -1) {
        traj.push({xi, yi});
        tie(xi, yi) = from[xi][yi];
      }
      traj.push({xi, yi});

      vector<int> commands;
      int lxi = -1, ci = -1;

      while (!traj.empty()) {
        auto [xi, yi] = traj.top();
        traj.pop();

        if (xi == lxi - 1 || (xi == 0 && lxi == 0)) commands.push_back(ci);
        lxi = xi;
        ci++;
      }

      cout << commands.size() << '\n';
      for (int e : commands) cout << e << " 1\n";
      return;
    }

    if (x == 0) {
      if (!vis[x + 1][y + 1] && board[x + 1][y + 1] == '.') vis[x + 1][y + 1] = 1, from[x + 1][y + 1] = {x, y}, q.push({x + 1, y + 1});
      if (!vis[x][y + 1] && board[x][y + 1] == '.') vis[x][y + 1] = 1, from[x][y + 1] = {x, y}, q.push({x, y + 1});
    }
    else if (x == 9) {
      if (!vis[x][y + 1] && board[x][y + 1] == '.') vis[x][y + 1] = 1, from[x][y + 1] = {x, y}, q.push({x, y + 1});
      if (!vis[x - 1][y + 1] && board[x - 1][y + 1] == '.') vis[x - 1][y + 1] = 1, from[x - 1][y + 1] = {x, y}, q.push({x - 1, y + 1});
    }
    else {
      if (!vis[x + 1][y + 1] && board[x + 1][y + 1] == '.') vis[x + 1][y + 1] = 1, from[x + 1][y + 1] = {x, y}, q.push({x + 1, y + 1});
      if (!vis[x - 1][y + 1] && board[x - 1][y + 1] == '.') vis[x - 1][y + 1] = 1, from[x - 1][y + 1] = {x, y}, q.push({x - 1, y + 1});
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
