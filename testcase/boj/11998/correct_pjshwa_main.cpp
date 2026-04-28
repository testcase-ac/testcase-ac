#include <bits/stdc++.h>
#define tii tuple<int, int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 101;
bool vis[MAX][MAX];

int main() {
  fast_io();

  int x, y, k, m;
  cin >> x >> y >> k >> m;

  queue<tii> q;
  q.push({0, 0, 0});
  vis[0][0] = true;

  int ans = m;
  while (!q.empty()) {
    auto [cx, cy, ck] = q.front();
    q.pop();

    ans = min(ans, abs(cx + cy - m));
    if (ck == k) continue;

    if (!vis[x][cy]) vis[x][cy] = true, q.push({x, cy, ck + 1});
    if (!vis[cx][y]) vis[cx][y] = true, q.push({cx, y, ck + 1});

    if (!vis[0][cy]) vis[0][cy] = true, q.push({0, cy, ck + 1});
    if (!vis[cx][0]) vis[cx][0] = true, q.push({cx, 0, ck + 1});

    int xdiff = x - cx, xpour = min(xdiff, cy);
    int ydiff = y - cy, ypour = min(ydiff, cx);
    if (!vis[cx + xpour][cy - xpour]) vis[cx + xpour][cy - xpour] = true, q.push({cx + xpour, cy - xpour, ck + 1});
    if (!vis[cx - ypour][cy + ypour]) vis[cx - ypour][cy + ypour] = true, q.push({cx - ypour, cy + ypour, ck + 1});
  }

  cout << ans << '\n';
}
