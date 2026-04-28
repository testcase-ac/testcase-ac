#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e3;
int n;
int board[MAX][MAX];
bool vis[MAX][MAX];

bool do_search(int diff) {
  queue<pii> q;
  q.push({0, 0});
  int x, y, cv;

  memset(vis, false, sizeof(vis));
  while (!q.empty()) {
    tie(x, y) = q.front();
    q.pop();

    if (vis[x][y]) continue;
    vis[x][y] = true;
    cv = board[x][y];

    if (x == n - 1 && y == n - 1) return true;

    if (x > 0 && !vis[x - 1][y] && abs(cv - board[x - 1][y]) <= diff) q.push({x - 1, y});
    if (y > 0 && !vis[x][y - 1] && abs(cv - board[x][y - 1]) <= diff) q.push({x, y - 1});
    if (x < n - 1 && !vis[x + 1][y] && abs(cv - board[x + 1][y]) <= diff) q.push({x + 1, y});
    if (y < n - 1 && !vis[x][y + 1] && abs(cv - board[x][y + 1]) <= diff) q.push({x, y + 1});
  }

  return false;
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> board[i][j];

  int left = 0;
  int right = 1e9 + 1;
  int mid = (left + right) / 2;

  while (left < right) {
    if (do_search(mid)) right = mid;
    else left = mid + 1;

    mid = (left + right) / 2;
  }

  cout << mid;
}
