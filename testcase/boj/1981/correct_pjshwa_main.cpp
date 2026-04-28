#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int n;
int board[100][100];
bool vis[100][100];

bool reachable(int diff) {
  queue<pii> q;
  int x, y, mx;

  for (int mn = 0; mn <= 200 - diff; mn++) {
    memset(vis, false, sizeof(vis));
    mx = mn + diff;

    if (board[0][0] <= mx && board[0][0] >= mn) q.push({0, 0});
    while (!q.empty()) {
      tie(x, y) = q.front();
      q.pop();

      if (vis[x][y]) continue;
      vis[x][y] = true;

      if (x == n - 1 && y == n - 1) return true;

      if (x > 0 && !vis[x - 1][y] && board[x - 1][y] <= mx && board[x - 1][y] >= mn) q.push({x - 1, y});
      if (y > 0 && !vis[x][y - 1] && board[x][y - 1] <= mx && board[x][y - 1] >= mn) q.push({x, y - 1});
      if (x < n - 1 && !vis[x + 1][y] && board[x + 1][y] <= mx && board[x + 1][y] >= mn) q.push({x + 1, y});
      if (y < n - 1 && !vis[x][y + 1] && board[x][y + 1] <= mx && board[x][y + 1] >= mn) q.push({x, y + 1});
    }
  }

  return false;
}

int main() {
  fast_io();

  cin >> n;
  int minv = 1e9, maxv = -1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> board[i][j];
      minv = min(minv, board[i][j]);
      maxv = max(maxv, board[i][j]);
    }
  }

  int left = 0;
  int right = maxv - minv;
  int mid = (left + right) / 2;

  while (left < right) {
    if (reachable(mid)) right = mid;
    else left = mid + 1;

    mid = (left + right) / 2;
  }

  cout << mid << '\n';
}
