#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int a[MAX][MAX];
pii from[MAX][MAX];
bool vis[MAX][MAX];

void solve() {
  for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) cin >> a[i][j];
  int r, c;
  cin >> r >> c;

  queue<tuple<int, int, int>> q;
  q.push({r, c, 0});
  vis[r][c] = true;

  while (!q.empty()) {
    auto [i, j, c] = q.front(); q.pop();

    if (a[i][j] == 1) {
      cout << c << '\n';
      return;
    }

    for (int k = 0; k < 4; k++) {
      int nx = i + dx[k], ny = j + dy[k];
      if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5) continue;
      if (a[nx][ny] != -1 && !vis[nx][ny]) {
        q.push({nx, ny, c + 1});
        vis[nx][ny] = true;
      }
    }

    int nx, ny;
    nx = i - 1;
    while (nx >= 0 && a[nx][j] != -1) {
      if (nx == 0 || a[nx - 1][j] == -1 || a[nx][j] == 7) {
        if (!vis[nx][j]) {
          q.push({nx, j, c + 1});
          vis[nx][j] = true;
        }
        break;
      }
      nx--;
    }
    nx = i + 1;
    while (nx < 5 && a[nx][j] != -1) {
      if (nx == 4 || a[nx + 1][j] == -1 || a[nx][j] == 7) {
        if (!vis[nx][j]) {
          q.push({nx, j, c + 1});
          vis[nx][j] = true;
        }
        break;
      }
      nx++;
    }
    ny = j - 1;
    while (ny >= 0 && a[i][ny] != -1) {
      if (ny == 0 || a[i][ny - 1] == -1 || a[i][ny] == 7) {
        if (!vis[i][ny]) {
          q.push({i, ny, c + 1});
          vis[i][ny] = true;
        }
        break;
      }
      ny--;
    }
    ny = j + 1;
    while (ny < 5 && a[i][ny] != -1) {
      if (ny == 4 || a[i][ny + 1] == -1 || a[i][ny] == 7) {
        if (!vis[i][ny]) {
          q.push({i, ny, c + 1});
          vis[i][ny] = true;
        }
        break;
      }
      ny++;
    }
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
