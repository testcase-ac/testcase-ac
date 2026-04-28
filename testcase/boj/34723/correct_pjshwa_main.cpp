#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int P, M, C, X, ans = -1; cin >> P >> M >> C >> X;
  for (int p = 1; p <= P; ++p) for (int m = 1; m <= M; ++m) for (int c = 1; c <= C; ++c) {
    int val = abs((p + m) * (m + c) - X);
    if (ans == -1 || val < ans) ans = val;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
