#include <bits/stdc++.h>
#define TIMES(n) for (int i = 0; i < n; i++)
#define pii pair<int, int>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const pii dirs[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int maze[100][100];
bool vis[100][100];
int main() {
  fast_io();

  int t, h, w, o, f, xs, ys, xe, ye, x, y, l;
  cin >> t;

  while (t--) {
    memset(maze, 0, sizeof(maze));
    memset(vis, 0, sizeof(vis));
    cin >> h >> w >> o >> f >> xs >> ys >> xe >> ye;
    TIMES(o) {
      cin >> x >> y >> l;
      maze[x - 1][y - 1] = l;
    }

    // {{xpos, ypos}, force}
    queue<pair<pii, int>> traj;
    traj.push({{xs - 1, ys - 1}, f});

    pii pos;
    int dx, dy, nx, ny;
    bool found = false;
    while (!traj.empty()) {
      tie(pos, f) = traj.front();
      tie(x, y) = pos;
      traj.pop();

      if (vis[x][y]) continue;
      vis[x][y] = true;

      if (x == xe - 1 && y == ye - 1) {
        cout << "잘했어!!\n";
        found = true;
        break;
      }

      if (f == 0) continue;

      for (int i = 0; i < 4; i++) {
        tie(dx, dy) = dirs[i];
        nx = x + dx;
        ny = y + dy;
        if (nx > h - 1 || nx < 0 || ny > w - 1 || ny < 0) continue;
        if (vis[nx][ny]) continue;
        if (maze[nx][ny] - maze[x][y] > f) continue;

        traj.push({{nx, ny}, f - 1});
      }
    }

    if (!found) cout << "인성 문제있어??\n";
  }

}
