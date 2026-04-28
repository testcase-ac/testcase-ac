#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  ll x, y, p; cin >> x >> y >> p;
  ll xmin = x - p, xmax = x + p, ymin = y - p, ymax = y + p;

  ll ans = 0;
  for (int i = 1; i < N; ++i) {
    cin >> x >> y >> p;

    ll cxmin = x - p, cxmax = x + p, cymin = y - p, cymax = y + p;

    ll xdist, ydist;

    // already overlaps
    if (cxmin <= xmax && cxmax >= xmin) xdist = 0;
    else xdist = min(abs(cxmin - xmax), abs(cxmax - xmin));

    if (cymin <= ymax && cymax >= ymin) ydist = 0;
    else ydist = min(abs(cymin - ymax), abs(cymax - ymin));

    // enlarge prev rectangle until it overlaps
    ll mov = max(xdist, ydist);
    ans += mov;
    xmin -= mov; xmax += mov; ymin -= mov; ymax += mov;

    // overlapping rectangle is the new rectangle
    xmax = min(xmax, cxmax); xmin = max(xmin, cxmin);
    ymax = min(ymax, cymax); ymin = max(ymin, cymin);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
