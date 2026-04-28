#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
} 

void solve() {
  ll A, B, K; cin >> A >> B >> K;

  ll S = A + B, ans = 1;
  for (ll f = 1; f * f <= S; ++f) {
    if (S % f) continue;

    for (ll g : {f, S / f}) {
      ll R = A % g;
      if (min(R, g - R) <= K) {
        ans = max(ans, g);
      }
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
