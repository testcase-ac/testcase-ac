#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll H1, H2, H3, N, ans = 0; cin >> H1 >> H2 >> H3 >> N;
  if (N & 1) ans += H1;
  ans += H2 * ((N + 1) / 2);
  ans += H3 * N;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
