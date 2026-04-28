#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<pii> A(N);
  for (int i = 0; i < N; i++) {
    int x, y; cin >> x >> y;
    A[i] = {x, y};
  }
  sort(A.begin(), A.end());

  vector<int> d(N, 1); int ans = 0;
  for (int i = 0; i < N; i++) {
    auto [cx, cy] = A[i];
    for (int j = 0; j < i; j++) {
      auto [px, py] = A[j];
      if (px < cx && py < cy) {
        d[i] = max(d[i], d[j] + 1);
      }
    }
    ans = max(ans, d[i]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
