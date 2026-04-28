#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, x; cin >> N >> x;

  ll d = N - x, ans = 0;
  for (ll f = 1; f * f <= d; f++) {
    if (d % f) continue;

    vector<ll> C{f};
    if (f * f != d) C.push_back(d / f);
    for (auto c : C) {
      if (c > x) ans += c;
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
