#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;
  vector<pii> a(n);
  set<pii> u;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    a[i] = {x, y};
    u.insert(a[i]);
  }

  set<pii> ans;
  auto [ox, oy] = a[0];
  for (int i = 1; i < n; i++) {
    auto [px, py] = a[i];
    int xd = px - ox, yd = py - oy;

    bool able = true;
    for (int j = 0; j < n; j++) {
      auto [ux, uy] = a[j];
      able &= (u.count({ux - xd, uy - yd}) || u.count({ux + xd, uy + yd}));
    }

    if (able) ans.insert({xd, yd}), ans.insert({-xd, -yd});
  }

  cout << ans.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
