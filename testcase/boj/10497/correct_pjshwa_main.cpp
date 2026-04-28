#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int M; cin >> M;
  vector<tuple<int, int, int, int>> R;
  vector<tuple<int, int, int>> C;
  while (M--) {
    string type; cin >> type;
    if (type == "rectangle") {
      int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
      R.emplace_back(x1, y1, x2, y2);
    } else {
      int x, y, r; cin >> x >> y >> r;
      C.emplace_back(x, y, r);
    }
  }

  int Q; cin >> Q;
  while (Q--) {
    int x, y, cnt = 0; cin >> x >> y;
    for (auto [x1, y1, x2, y2] : R) {
      if (x1 <= x && x <= x2 && y1 <= y && y <= y2) ++cnt;
    }
    for (auto [cx, cy, r] : C) {
      if ((cx - x) * (cx - x) + (cy - y) * (cy - y) <= r * r) ++cnt;
    }
    cout << cnt << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
