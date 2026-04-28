#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll a, b, ans = 0; cin >> a >> b;

  while (a % 2 == 0) a /= 2, b *= 2;
  ans = max(ans, 2 * (a + b));
  while (b % 2 == 0) b /= 2, a *= 2;
  ans = max(ans, 2 * (a + b));

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
