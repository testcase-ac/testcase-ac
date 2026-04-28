#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll C(int n, int k) {
  ll ans = 1;
  for (int i = 1; i <= k; i++) {
    ans *= (n - i + 1);
    ans /= i;
  }
  return ans;
}

ll U(int n, int k) {
  ll a = C(n, k), sym;
  if (n % 2 == 0 && (k & 1)) sym = 0;
  else sym = C(n / 2, k / 2);

  return (a + sym) / 2;
}

void solve() {
  int n, k;
  cin >> n >> k;

  ll ans = 0;
  for (int l = 0; l <= n; l++) {
    int r = k - l;
    if (r < 0 || r > n) continue;

    if (l == r) ans += 2 * U(n, l);
    else ans += U(n, l);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
