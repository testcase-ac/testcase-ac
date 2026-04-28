#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll X, Y, W, S; cin >> X >> Y >> W >> S;

  ll ans;
  if (W > S) {
    ans = max(X, Y) * S;
    if ((X + Y) % 2 == 1) ans += W - S;
  }
  else if (2 * W > S) {
    ans = min(X, Y) * S;
    ans += (max(X, Y) - min(X, Y)) * W;
  }
  else ans = (X + Y) * W;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
