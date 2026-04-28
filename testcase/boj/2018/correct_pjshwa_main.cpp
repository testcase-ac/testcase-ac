#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll n;
  cin >> n;
  n *= 2;

  int ans = 0;
  for (ll i = 1; i * i <= n; i++) {
    if (n % i) continue;

    if (i * i == n) {
      int u = n / i - i + 1;
      if (u > 0 && u % 2 == 0) ans++;
    }
    else {
      for (int k : {i, n / i}) {
        int u = n / k - k + 1;
        if (u > 0 && u % 2 == 0) ans++;
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
