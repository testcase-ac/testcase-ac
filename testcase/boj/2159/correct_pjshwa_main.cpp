#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 1e5, INF = 1e18;
const int dx[5] = {0, 0, 0, 1, -1}, dy[5] = {0, 1, -1, 0, 0};
pii A[MAX];
ll d[MAX][5];

void solve() {
  int N, X, Y; cin >> N >> X >> Y;
  for (int i = 0; i < N; i++) {
    int x, y; cin >> x >> y;
    A[i] = {x, y};

    for (int k = 0; k < 5; k++) d[i][k] = 1e18;
  }

  auto [cx, cy] = A[0];
  for (int k = 0; k < 5; k++) {
    int px = cx + dx[k], py = cy + dy[k];
    d[0][k] = abs(px - X) + abs(py - Y);
  }

  for (int i = 1; i < N; i++) {
    auto [cx, cy] = A[i];
    auto [px, py] = A[i - 1];

    for (int k = 0; k < 5; k++) {
      int ox = cx + dx[k], oy = cy + dy[k];

      for (int pk = 0; pk < 5; pk++) {
        int opx = px + dx[pk], opy = py + dy[pk];
        ll cost = d[i - 1][pk] + abs(ox - opx) + abs(oy - opy);
        d[i][k] = min(d[i][k], cost);
      }
    }
  }

  ll ans = INF;
  for (int k = 0; k < 5; k++) ans = min(ans, d[N - 1][k]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
