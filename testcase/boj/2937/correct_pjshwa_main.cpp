#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, m;
  cin >> n >> m;
  map<int, vector<int>> xs;
  vector<int> ys;

  for (int i = 0; i < n; i++) {
    int xi, yi;
    cin >> xi >> yi;
    xi = (xi + 1) / 2;
    yi = (yi + 1) / 2;

    xs[xi].push_back(yi);
    ys.push_back(yi);
    sr.inc(yi);
  }
  compress(ys);

  lw = 0, rw = n;
  int ans = 1e9;
  for (auto [xi, yv] : xs) {
    for (int yi : yv) {
      lw++;
      rw--;
      sl.inc(yi);
      sr.dec(yi);
    }

    int left = 0, right = MAXP;
    while (right - left >= 3) {
      int mid1 = left + (right - left) / 3;
      int mid2 = right - (right - left) / 3;
      if (mmax(mid1) < mmax(mid2)) left = mid1;
      else right = mid2;
    }
    for (int i = left; i <= right; i++) ans = min(ans, -mmax(i));
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
