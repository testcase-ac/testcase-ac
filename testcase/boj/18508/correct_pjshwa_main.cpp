#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  map<int, vector<int>> F;
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    F[y].push_back(x);
  }

  vector<tuple<int, int, int, int>> ans;
  vector<pair<int, int>> R;

  auto sq_len = [&](int x1, int y1, int x2, int y2) {
    int maxx = max(x1, x2), minx = min(x1, x2);
    int maxy = max(y1, y2), miny = min(y1, y2);
    int len = max(maxx - minx, maxy - miny);
    return len;
  };

  auto add_point = [&](int x1, int y1, int x2, int y2) {
    int len = sq_len(x1, y1, x2, y2);
    int maxx = max(x1, x2), maxy = max(y1, y2);
    ans.emplace_back(maxx - len, maxy - len, maxx, maxy);
  };

  vector<pii> cur;
  int px = -1, py = -1;
  for (auto& [y, xv] : F) {
    for (int x : xv) cur.emplace_back(x, y);
    sort(cur.begin(), cur.end());

    while (cur.size() >= 2) {
      auto [x1, y1] = cur.back(); cur.pop_back();
      auto [x2, y2] = cur.back(); cur.pop_back();
      if (px != -1 && x2 <= px && px <= x1) {
        int plen = sq_len(px, py, x1, y1);
        ans.emplace_back(px, y1 - plen, px + plen, y1);

        px = -1, py = -1;
        cur.emplace_back(x2, y2);
      }
      else add_point(x1, y1, x2, y2);
    }

    if (cur.empty()) continue;
    auto [xr, yr] = cur.back(); cur.pop_back();
    if (px == -1) px = xr, py = yr;
    else {
      add_point(px, py, xr, yr);
      px = -1, py = -1;
    }
  }

  cout << "Yes\n";
  for (auto [x1, y1, x2, y2] : ans) {
    cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
