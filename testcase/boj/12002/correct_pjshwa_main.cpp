#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<pii> A;
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    A.emplace_back(x, y);
  }
  sort(A.begin(), A.end());

  ll ans = 1e18;
  for (int xl = 0; xl <= 3; ++xl) for (int xr = 0; xl + xr <= 3; ++xr) {
    int xmin = A[xl].first, xmax = A[N - 1 - xr].first;

    vector<int> ys;
    for (int i = xl; i < N - xr; ++i) ys.push_back(A[i].second);
    sort(ys.begin(), ys.end());

    int Z = ys.size();
    for (int yl = 0; yl <= 3; ++yl) for (int yr = 0; yl + yr <= 3; ++yr) {
      if (xl + xr + yl + yr > 3) continue;
      int ymin = ys[yl], ymax = ys[Z - 1 - yr];
      ans = min(ans, (ll)(xmax - xmin) * (ymax - ymin));
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
