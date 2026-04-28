#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 8, INF = 0x3f3f3f3f;
const int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};
int cdist[MAXN][MAXN];

pii to_pos(string s) {
  return {s[0] - 'a', s[1] - '1'};
}

void solve() {
  string As, Bs; cin >> As >> Bs;
  auto [Ax, Ay] = to_pos(As); auto [Bx, By] = to_pos(Bs);

  memset(cdist, 0x3f, sizeof(cdist));
  queue<pii> q; q.emplace(Ax, Ay); cdist[Ax][Ay] = 0;
  while (!q.empty()) {
    auto [x, y] = q.front(); q.pop();
    for (int k = 0; k < 8; ++k) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || nx >= MAXN || ny < 0 || ny >= MAXN) continue;
      if (cdist[nx][ny] == INF) {
        cdist[nx][ny] = cdist[x][y] + 1;
        q.emplace(nx, ny);
      }
    }
  }
  cout << cdist[Bx][By] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
