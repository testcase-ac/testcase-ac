#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll sum_gs_upto(ll a, ll d, ll n) {
  if (n == 0) return 0;
  return n * a + n * (n - 1) / 2 * d;
}

void solve() {
  ll a, d, q;
  cin >> a >> d >> q;

  int g = __gcd(a, d);

  while (q--) {
    ll o, l, r;
    cin >> o >> l >> r;

    if (o == 1) cout << sum_gs_upto(a, d, r) - sum_gs_upto(a, d, l - 1) << '\n';
    if (o == 2) {
      if (l == r) cout << a + d * (l - 1) << '\n';
      else cout << g << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
