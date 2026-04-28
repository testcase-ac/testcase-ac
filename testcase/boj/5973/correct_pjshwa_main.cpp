#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  vector<pii> points(n);
  map<pii, int> m;

  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    points[i] = {x, y};
  }

  for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
    auto [x1, x2] = points[i];
    auto [y1, y2] = points[j];
    m[{x1 + y1, x2 + y2}]++;
  }

  int ans = 0;
  for (auto [k, v] : m) {
    ans += v * (v - 1) / 2;
  }
  cout << ans << '\n';
}
