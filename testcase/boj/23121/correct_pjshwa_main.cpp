#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

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

ll modint(ll x, ll m) {
  ll ret = (x % m + m) % m;
  assert(0 <= ret && ret < m);
  return ret;
}

int P;
void solve() {
  ll a, b, c, d; cin >> a >> b >> c >> d;
  ll S = (a + b) % P, E = (c + d) % P;
  if (S != E) return cout << "-1\n", void();

  ll Sinv = lpow(S, P - 2, P);
  a = (a * Sinv) % P; c = (c * Sinv) % P;

  ll lb = a, ub = a, ans = 0;
  while (1) {
    if (ub - lb > P) break;

    ll lbp = modint(lb, P), ubp = modint(ub, P);
    if (ubp < lbp) {
      if (c <= ubp || lbp <= c) break;
    }
    else {
      if (lbp <= c && c <= ubp) break;
    }
    ++ans;
    lb = 2 * lb - 1, ub = 2 * ub;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> P >> t;
  while (t--) solve();
}
