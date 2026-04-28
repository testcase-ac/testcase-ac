#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll n;
  cin >> n;
  n *= 2;

  int ans = 0;
  for (ll i = 2; i * i <= n; i++) {
    if (n % i) continue;

    for (ll f : {i, n / i}) {
      ll u = n / f - f + 1;
      if (u % 2 == 0 && u / 2 >= 1) ans++;

      if (f == n / f) break;
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
