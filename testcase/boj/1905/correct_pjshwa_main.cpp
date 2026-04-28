#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N >> N >> N;
  vector<tuple<int, int, int, int, ll>> A;

  ll ans = 0;
  for (int i = 0; i < N; ++i) {
    int lx, ly, lz, px, py; cin >> lx >> ly >> lz >> px >> py;
    int xl = px, yl = py, xu = px + lx, yu = py + ly;

    ll h = lz;
    for (auto& [pxl, pyl, pxu, pyu, ph] : A) {
      // check if rect overlaps
      if (xl >= pxu || xu <= pxl || yl >= pyu || yu <= pyl) continue;
      h = max(h, ph + lz);
    }
    A.emplace_back(xl, yl, xu, yu, h); ans = max(ans, h);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
