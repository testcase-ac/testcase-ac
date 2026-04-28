#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, p; ll s; cin >> n >> p >> s;

  vector<pii> A;
  for (int i = 0; i < n; ++i) {
    int x, y; cin >> x >> y;
    A.emplace_back(x, y);
  }

  --p;
  queue<int> Q; vector<bool> vis(n);
  Q.push(p); vis[p] = true;

  while (!Q.empty()) {
    auto [x, y] = A[Q.front()]; Q.pop();
    for (int i = 0; i < n; ++i) {
      auto [nx, ny] = A[i];
      ll dis_sq = (ll)(x - nx) * (x - nx) + (ll)(y - ny) * (y - ny);
      if (dis_sq > s * s || vis[i]) continue;
      Q.push(i); vis[i] = true;
    }
  }

  double ans = s; auto [sx, sy] = A[p];
  for (int i = 0; i < n; ++i) {
    if (!vis[i]) continue;
    auto [nx, ny] = A[i];
    ll dis_sq = (ll)(sx - nx) * (sx - nx) + (ll)(sy - ny) * (sy - ny);
    ans = max(ans, sqrt(dis_sq) + s);
  }
  cout << fixed << setprecision(3) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
