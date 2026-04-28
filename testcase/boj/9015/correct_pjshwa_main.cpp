#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;

  vector<pii> v(n);
  set<pii> s;
  for (int i = 0; i < n; ++i) {
    cin >> v[i].first >> v[i].second;
    s.insert(v[i]);
  }

  int ans = 0;
  for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
    auto [a, b] = v[i];
    auto [c, d] = v[j];

    int x1 = a + c + b - d, y1 = b + d - a + c;
    int x2 = a + c + d - b, y2 = a + b - c + d;

    if (x1 % 2 || y1 % 2 || x2 % 2 || y2 % 2) continue;
    if (s.count({x1 / 2, y1 / 2}) && s.count({x2 / 2, y2 / 2})) {
      ans = max(ans, (c - a) * (c - a) + (d - b) * (d - b));
    }
  }

  cout << ans / 2 << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
