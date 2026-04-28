#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

// Find x s.t. a^x = b (mod m)
// Assumes a < m, b < m
ll discrete_log(ll a, ll b, ll m) {
  ll n = ceil(sqrt(m));
  unordered_map<ll, ll> vals;

  for (int p = 0; p * n < m; ++p) vals[lpow(a, p * n, m)] = p;

  ll mx = -1;
  for (int q = 0; q <= n; ++q) {
    ll cur = (lpow(a, q, m) * b) % m;
    if (vals.count(cur)) {
      ll cv = (vals[cur] * n - q + m) % m;
      if (mx == -1) mx = cv;
      else mx = min(mx, cv);
    }
  }

  return mx;
}

int main() {
  fast_io();

  ll p, b, n;
  while (cin >> p >> b >> n) {
    ll ans = discrete_log(b, n, p);
    if (ans == -1) cout << "no solution\n";
    else cout << ans << '\n';
  }
}
