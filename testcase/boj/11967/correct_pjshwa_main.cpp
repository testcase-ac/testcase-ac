#include <bits/stdc++.h>
using namespace std;

const int MAX = 100;
bool light[MAX][MAX], vis[MAX][MAX];
int n;
queue<pair<int, int>> switches[MAX][MAX];

int bfs() {
  queue<pair<int, int>> q;
  q.push({0, 0});
  memset(vis, 0, sizeof(vis));
  vis[0][0] = true;

  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();

    while (!switches[x][y].empty()) {
      auto [a, b] = switches[x][y].front();
      switches[x][y].pop();
      light[a][b] = true;
    }

    if (x - 1 >= 0 && light[x - 1][y] && !vis[x - 1][y]) vis[x - 1][y] = true, q.push({x - 1, y});
    if (x + 1 < n && light[x + 1][y] && !vis[x + 1][y]) vis[x + 1][y] = true, q.push({x + 1, y});
    if (y - 1 >= 0 && light[x][y - 1] && !vis[x][y - 1]) vis[x][y - 1] = true, q.push({x, y - 1});
    if (y + 1 < n && light[x][y + 1] && !vis[x][y + 1]) vis[x][y + 1] = true, q.push({x, y + 1});
  }

  int res = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (light[i][j]) res++;
  return res;
}

int main() {
  int m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int x, y, a, b;
    cin >> x >> y >> a >> b;
    switches[x - 1][y - 1].push({a - 1, b - 1});
  }

  light[0][0] = true;
  int prev = 0;
  while (1) {
    int res = bfs();
    if (prev == res) break;
    prev = res;
  }
  cout << prev << '\n';
}
