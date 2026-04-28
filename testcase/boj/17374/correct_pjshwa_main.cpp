#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll P, Q, A, B, C, D; cin >> P >> Q >> A >> B >> C >> D;

  ll R = (Q / C) * D;
  while (P >= A) P -= A, R += B;

  ll l = 0, r = R / B + 1, ans = min(P, R);
  while (l < r) {
    ll m = (l + r) / 2;

    ll cP = P + m * A, cR = R - m * B;
    if (cP >= cR) r = m;
    else l = m + 1;
  }

  for (int k = -3; k <= 3; k++) {
    ll m = l + k;
    ll cP = P + m * A, cR = R - m * B;
    ans = max(ans, min(cP, cR));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
