#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7, INV2 = 500000004;

ll lev(int i) {
  ll ret = 0, pw = 1;
  while (pw <= i) {
    pw *= 2;
    ++ret;
  }
  return ret;
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

void solve() {
  ll a, m;
  cin >> a >> m;

  ll tsz = lpow(2, a, MOD);
  map<ll, ll> v_by_rem[50];
  
  while (m--) {
    int v;
    cin >> v;

    ll l = lev(v);
    ll mo = lpow(2, l, 1e18), r = v;
    ll cur = (tsz * lpow(INV2, l, MOD)) % MOD;

    // cout << "l: " << l << " mo: " << mo << " r: " << r << " cur: " << cur << '\n';

    cur = (cur - v_by_rem[l][r] + MOD) % MOD;
    cout << cur << '\n';

    while (mo) {
      r %= mo;
      v_by_rem[l][r] = (v_by_rem[l][r] + cur) % MOD;
      l--; mo /= 2;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
