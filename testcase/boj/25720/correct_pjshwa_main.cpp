#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll p, a, b, c;
ll nx(ll x) {
  ll term1 = x, term2 = x;
  term1 = (term1 * x) % p;
  term1 = (term1 * a) % p;
  term2 = (term2 * b) % p;

  return (term1 + term2 + c) % p;
}

void solve() {
  ll n, m, x;
  cin >> n >> m >> p >> x >> a >> b >> c;

  map<ll, int> u;
  for (int i = 1; i <= n; i++) {
    x = nx(x);

    if (!u.count(x)) u[x] = i;
  }

  ll ans = 0;
  for (int i = 0; i < m; i++) {
    x = nx(x);

    if (u.count(x)) {
      ll tlen = m - i, slen = n - u[x] + 1;
      ans = max(ans, min(tlen, slen));
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
