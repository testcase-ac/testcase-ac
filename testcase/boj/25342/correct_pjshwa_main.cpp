#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll lcm(ll a, ll b) {
  return a / __gcd(a, b) * b;
}

void solve() {
  int N;
  cin >> N;

  ll ans = 0, ai, aj, ak;
  for (ll i = max(1, N - 15); i <= N; i++) for (ll j = i + 1; j <= N; j++) for (ll k = j + 1; k <= N; k++) {
    ans = max(ans, lcm(k, lcm(i, j)));
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
