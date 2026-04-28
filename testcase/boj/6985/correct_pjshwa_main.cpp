#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool vis[16][16][7][7], obs[16][16];

void solve() {
  int x, y, sx, sy, ex, ey;
  cin >> x >> y >> sx >> sy >> ex >> ey;

  memset(obs, 0, sizeof(obs));
  memset(vis, 0, sizeof(vis));

  int p;
  cin >> p;
  while (p--) {
    int oxs, oys, oxe, oye;
    cin >> oxs >> oxe >> oys >> oye;
    for (int i = oxs; i <= oxe; ++i) {
      for (int j = oys; j <= oye; ++j) {
        obs[i][j] = 1;
      }
    }
  }

  int bias = 3;
  queue<tuple<int, int, int, int, int>> q;
  q.push({sx, sy, bias, bias, 0});
  vis[sx][sy][bias][bias] = true;

  while (!q.empty()) {
    auto [cx, cy, dx, dy, cnt] = q.front();
    q.pop();

    if (cx == ex && cy == ey) {
      cout << "Optimal solution takes " << cnt << " hops." << '\n';
      return;
    }

    for (int nx = dx - 1; nx <= dx + 1; nx++) for (int ny = dy - 1; ny <= dy + 1; ny++) {
      if (nx < 0 || ny < 0 || nx >= 7 || ny >= 7) continue;
      int npx = cx + (nx - bias), npy = cy + (ny - bias);
      if (npx < 0 || npy < 0 || npx >= x || npy >= y) continue;
      if (vis[npx][npy][nx][ny] || obs[npx][npy]) continue;
      vis[npx][npy][nx][ny] = true;
      q.push({npx, npy, nx, ny, cnt + 1});
    }
  }

  cout << "No solution.\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
