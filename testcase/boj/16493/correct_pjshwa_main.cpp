#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;
  vector<pii> A(M);
  for (auto& [x, y] : A) cin >> x >> y;

  int ans = 0;
  for (int s = 0; s < (1 << M); s++) {
    int xsum = 0, ysum = 0;
    for (int i = 0; i < M; i++) {
      if (!(s & (1 << i))) continue;
      auto [x, y] = A[i];
      xsum += x; ysum += y;
    }
    if (xsum <= N) ans = max(ans, ysum);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
