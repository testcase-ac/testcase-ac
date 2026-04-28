#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 64;
int board[MAX + 10][MAX + 10], vis[MAX + 10][MAX + 10];

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      cin >> board[i][j];
    }
  }

  queue<pii> q;
  q.push({1, 1});
  vis[1][1] = 1;

  while (!q.empty()) {
    auto [x, y] = q.front(); q.pop();

    if (x == N && y == N) {
      cout << "HaruHaru\n";
      return;
    }

    if (x + board[x][y] <= N && !vis[x + board[x][y]][y]) {
      q.push({x + board[x][y], y});
      vis[x + board[x][y]][y] = 1;
    }
    if (y + board[x][y] <= N && !vis[x][y + board[x][y]]) {
      q.push({x, y + board[x][y]});
      vis[x][y + board[x][y]] = 1;
    }
  }

  cout << "Hing\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
