#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;

void solve() {
  int k;
  cin >> k;

  vector<pii> a;
  int x = 0, y = 0;

  int minx = INF, miny = INF, maxx = -INF, maxy = -INF;
  for (int i = 0; i < 6; i++) {
    a.push_back({x, y});
    minx = min(minx, x), miny = min(miny, y);
    maxx = max(maxx, x), maxy = max(maxy, y);

    int d, m;
    cin >> d >> m;
    if (d == 1) x += m;
    if (d == 2) x -= m;
    if (d == 3) y -= m;
    if (d == 4) y += m;
  }

  for (int i = 0; i < 6; i++) {
    auto [x, y] = a[i];
    if (x != maxx && x != minx && y != maxy && y != miny) {
      int pi = (i + 5) % 6, ni = (i + 1) % 6;
      int xdiff = max(abs(a[pi].first - x), abs(x - a[ni].first));
      int ydiff = max(abs(a[pi].second - y), abs(y - a[ni].second));

      int ans = (maxx - minx) * (maxy - miny) - xdiff * ydiff;
      ans *= k;
      cout << ans << '\n';
      return;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
