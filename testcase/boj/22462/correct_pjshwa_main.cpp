#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int dx[6] = {0, 1, 1, 0, -1, -1};
const int dy_e[6] = {1, 0, -1, -1, -1, 0};
const int dy_o[6] = {1, 1, 0, -1, 0, 1};
const int MAX = 500, BIAS = 250, INF = 0x3f3f3f3f;
int cdist[MAX][MAX][6], b[MAX][MAX];

void solve() {
  int sx, sy, gx, gy, n;
  cin >> sx >> sy >> gx >> gy >> n;
  for (int i = 0; i < n; i++) {
    int xi, yi;
    cin >> xi >> yi;
    b[xi + BIAS][yi + BIAS] = 1;
  }
  int lx, ly;
  cin >> lx >> ly;

  for (int x = -lx; x <= lx; x++) for (int y = -ly; y <= ly; y++) {
    for (int j = 0; j < 6; j++) cdist[x + BIAS][y + BIAS][j] = INF;
  }

  // 0-1 bfs
  deque<tuple<int, int, int>> dq;
  dq.push_back({sx + BIAS, sy + BIAS, 0});
  cdist[sx + BIAS][sy + BIAS][0] = 0;

  while (!dq.empty()) {
    auto [ux, uy, ut] = dq.front();
    dq.pop_front();

    int pk = abs((ux - BIAS) * (uy - BIAS) * ut) % 6;
    for (int k = 0; k < 6; k++) {
      int nx, ny, nt = (ut + 1) % 6;
      if (ux & 1) nx = ux + dx[k], ny = uy + dy_o[k];
      else nx = ux + dx[k], ny = uy + dy_e[k];

      if (nx - BIAS < -lx || nx - BIAS > lx || ny - BIAS < -ly || ny - BIAS > ly) continue;
      if (b[nx][ny]) continue;

      if (k == pk) {
        if (cdist[nx][ny][nt] > cdist[ux][uy][ut]) {
          cdist[nx][ny][nt] = cdist[ux][uy][ut];
          dq.push_front({nx, ny, nt});
        }
      }
      else {
        if (cdist[nx][ny][nt] > cdist[ux][uy][ut] + 1) {
          cdist[nx][ny][nt] = cdist[ux][uy][ut] + 1;
          dq.push_back({nx, ny, nt});
        }
      }
    }

    // stay in place
    int nt = (ut + 1) % 6;
    if (cdist[ux][uy][nt] > cdist[ux][uy][ut] + 1) {
      cdist[ux][uy][nt] = cdist[ux][uy][ut] + 1;
      dq.push_back({ux, uy, nt});
    }
  }

  int ans = INF;
  for (int j = 0; j < 6; j++) ans = min(ans, cdist[gx + BIAS][gy + BIAS][j]);

  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
