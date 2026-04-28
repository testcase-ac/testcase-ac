#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50, INF = 1e9 + 7;
pii a[MAX + 1];
int d[MAX + 1][101][101];

int r(int i, int x, int y) {
  if (i == 0) {
    if (x == 0 && y == 0) return 0;
    else return INF;
  }
  if (d[i][x][y] != -1) return d[i][x][y];

  auto [xi, yi] = a[i];
  int ret = r(i - 1, x, y);
  ret = min(ret, r(i - 1, max(x - xi, 0), max(y - yi, 0)) + 1);
  return d[i][x][y] = ret;
}

void solve() {
  int n, x, y;
  cin >> n >> x >> y;
  for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second;

  memset(d, -1, sizeof(d));
  int ans = r(n, x, y);
  if (ans == INF) cout << "-1\n";
  else {
    cout << ans << '\n';
    for (int i = 1; i <= n; i++) {
      if (ans == r(i, x, y)) {
        cout << i << '\n';
        break;
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
