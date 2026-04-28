#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
pii A[MAX + 1]; int d[MAX + 1][2];

void solve() {
  int n; cin >> n;
  for (int i = 1; i <= n; i++) {
    int x, y; cin >> x >> y;
    A[i] = {x, y};
  }

  d[1][0] = A[1].first; d[1][1] = A[1].second;
  for (int i = 2; i <= n; i++) {
    auto [cx, cy] = A[i];
    auto [px, py] = A[i - 1];
    d[i][0] = max(d[i - 1][0] + abs(cy - py) + cx, d[i - 1][1] + abs(cy - px) + cx);
    d[i][1] = max(d[i - 1][0] + abs(cx - py) + cy, d[i - 1][1] + abs(cx - px) + cy);
  }

  cout << max(d[n][0], d[n][1]) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
