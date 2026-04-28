#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, K; cin >> N >> M >> K;

  map<pii, int> t;
  for (int i = 0; i < N; i++) {
    int x, y; cin >> x >> y;

    int cx = x, cy = y;
    for (int j = 0; j < K; j++) {
      int g = __gcd(cx, cy);
      t[{cx / g, cy / g}]++;

      if (j & 1) cx += 2 * x;
      else cx += 2 * (M - x);
    }
  }

  int ans = 0;
  for (auto [_, cnt] : t) ans = max(ans, cnt);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
