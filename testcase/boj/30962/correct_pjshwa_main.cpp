#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXW = 1e5;
vector<pii> by_w[MAXW + 1];

void solve() {
  for (int x = -1000; x <= 1000; ++x) for (int y = -1000; y <= 1000; ++y) {
    int w = x * x + y * y;
    if (w <= MAXW) by_w[w].emplace_back(x, y);
  }

  int Q; cin >> Q;
  while (Q--) {
    int x1, y1, x2, y2, w; cin >> x1 >> y1 >> x2 >> y2 >> w;

    int ans = 0;
    for (auto& [x, y] : by_w[w]) {
      if (y * x2 >= x * y2 && y * x1 <= x * y1) ++ans;
    }
    cout << ans << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
