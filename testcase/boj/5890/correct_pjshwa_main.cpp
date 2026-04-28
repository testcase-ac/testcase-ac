#include <bits/stdc++.h>
typedef long long ll;
#define pll pair<ll, ll>
using namespace std;

const int MAX = 1e3;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
const ll INF = 1e14;
ll cdist[MAX * MAX + 1], ans = INF;
bool board[MAX][MAX];

void dijk(int s) {
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    int x = ui / 1000, y = ui % 1000;
    for (int k = 0; k < 4; k++) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || nx >= MAX || ny < 0 || ny >= MAX) {
        ans = min(ans, cdist[ui]);
        continue;
      }

      int di = board[nx][ny] ? 1 : 0;
      int vi = nx * 1000 + ny;
      if (cdist[vi] > wi + di) {
        cdist[vi] = wi + di;
        pq.push({wi + di, vi});
      }
    }
  }
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int m, x, y;
  cin >> m >> x >> y;
  while (m--) {
    int xi, yi;
    cin >> xi >> yi;
    board[xi - 1][yi - 1] = true;
  }
  fill(cdist, cdist + MAX * MAX + 1, INF);
  dijk(1000 * (x - 1) + y - 1);
  cout << ans << '\n';
}
