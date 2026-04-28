#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 200;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
int vis[MAX][MAX];

int main() {
  fast_io();

  int n, k, s, x, y;
  cin >> n >> k;
  vector<tuple<int, int, int>> origins;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    cin >> vis[i][j];
    if (vis[i][j]) origins.emplace_back(vis[i][j], i, j);
  }
  cin >> s >> x >> y;

  sort(origins.begin(), origins.end());
  queue<tuple<int, int, int>> q;
  for (auto &origin : origins) q.push({get<1>(origin), get<2>(origin), 0});

  while (!q.empty()) {
    auto [i, j, d] = q.front();
    q.pop();
    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || nj < 0 || ni >= n || nj >= n) continue;
      if (!vis[ni][nj] && d < s) {
        vis[ni][nj] = vis[i][j];
        q.push({ni, nj, d + 1});
      }
    }
  }

  cout << vis[x - 1][y - 1] << '\n';
}
