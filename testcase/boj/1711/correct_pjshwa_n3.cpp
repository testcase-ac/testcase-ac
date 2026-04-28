#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<pll> V;
  for (int i = 0; i < N; i++) {
    int x, y; cin >> x >> y;
    V.emplace_back(x, y);
  }

  ll ans = 0;
  for (int i = 0; i < N; i++) for (int j = i + 1; j < N; j++) for (int k = j + 1; k < N; k++) {
    auto [x1, y1] = V[i]; auto [x2, y2] = V[j]; auto [x3, y3] = V[k];

    // Check if the three points form a right triangle
    if ((x1 - x2) * (x1 - x3) + (y1 - y2) * (y1 - y3) == 0) ans++;
    else if ((x2 - x1) * (x2 - x3) + (y2 - y1) * (y2 - y3) == 0) ans++;
    else if ((x3 - x1) * (x3 - x2) + (y3 - y1) * (y3 - y2) == 0) ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
