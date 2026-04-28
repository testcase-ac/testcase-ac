#include <bits/stdc++.h>
typedef long long ll;
#define pii pair<int, int>
#define piipii pair<pii, pii>
using namespace std;

bool vis[1000][1000][11];
char board[1001][1001];
int main() {
  int n, m, k = 1;
  cin >> n >> m;

  for (int i = 0; i < n; i++) cin >> board[i];

  queue<piipii> mq;
  mq.push({{0, 0}, {1, k}});
  pii pos, dk;
  int x, y, cd, ck, ans = -1;

  while (!mq.empty()) {
    tie(pos, dk) = mq.front();
    tie(x, y) = pos;
    tie(cd, ck) = dk;
    mq.pop();

    if (vis[x][y][ck]) continue;
    vis[x][y][ck] = true;

    if (x == n - 1 && y == m - 1) {
      ans = cd;
      break;
    }

    if (x > 0) {
      if (board[x - 1][y] == '0') {
        if (!vis[x - 1][y][ck]) mq.push({{x - 1, y}, {cd + 1, ck}});
      }
      else if (ck) {
        if (!vis[x - 1][y][ck - 1]) mq.push({{x - 1, y}, {cd + 1, ck - 1}});
      }
    }
    if (y > 0) {
      if (board[x][y - 1] == '0') {
        if (!vis[x][y - 1][ck]) mq.push({{x, y - 1}, {cd + 1, ck}});
      }
      else if (ck) {
        if (!vis[x][y - 1][ck - 1]) mq.push({{x, y - 1}, {cd + 1, ck - 1}});
      }
    }
    if (x < n - 1) {
      if (board[x + 1][y] == '0') {
        if (!vis[x + 1][y][ck]) mq.push({{x + 1, y}, {cd + 1, ck}});
      }
      else if (ck) {
        if (!vis[x + 1][y][ck - 1]) mq.push({{x + 1, y}, {cd + 1, ck - 1}});
      }
    }
    if (y < m - 1) {
      if (board[x][y + 1] == '0') {
        if (!vis[x][y + 1][ck]) mq.push({{x, y + 1}, {cd + 1, ck}});
      }
      else if (ck) {
        if (!vis[x][y + 1][ck - 1]) mq.push({{x, y + 1}, {cd + 1, ck - 1}});
      }
    }
  }

  cout << ans << '\n';
}
