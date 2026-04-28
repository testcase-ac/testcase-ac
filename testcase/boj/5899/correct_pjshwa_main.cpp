#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;

  vector<tuple<int, int, pii>> xs;
  for (int i = 0; i < n; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    xs.emplace_back(x1, 0, make_pair(y2, y1));
    xs.emplace_back(x2, 1, make_pair(y2, y1));
  }
  sort(xs.begin(), xs.end());

  multiset<pii> ys;
  ll last = -1e9, ans = 0;
  for (auto& [x, o, p] : xs) {
    auto [y2, y1] = p;

    ll width = x - last, ysum = 0, ylast = -1e9, ydt = 0;
    for (auto [y, yo] : ys) {
      ll height = y - ylast;
      if (ydt) ysum += height;
      ylast = y;
      ydt += yo;
    }

    ans += width * ysum;

    if (o) {
      ys.erase(ys.lower_bound({y1, -1}));
      ys.erase(ys.lower_bound({y2, 1}));
    }
    else {
      ys.insert({y1, -1}), ys.insert({y2, 1});
    }

    last = x;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
