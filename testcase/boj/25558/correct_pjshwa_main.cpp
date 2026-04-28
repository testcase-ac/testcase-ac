#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N, sx, sy, ex, ey;
  cin >> N >> sx >> sy >> ex >> ey;

  ll ans, val = 1e18;
  for (int i = 1; i <= N; i++) {
    int Mi;
    cin >> Mi;

    ll cur = 0, cx = sx, cy = sy;
    for (int i = 0; i < Mi; i++) {
      int x, y;
      cin >> x >> y;
      cur += abs(cx - x) + abs(cy - y);
      cx = x, cy = y;
    }
    cur += abs(ex - cx) + abs(ey - cy);

    if (cur < val) ans = i, val = cur;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
