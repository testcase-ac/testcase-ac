#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6 + 10, MOD = 1e9 + 7;

struct SegmentTree {
  vector<ll> t; ll (*op)(ll, ll);
  SegmentTree(ll e, ll f(ll, ll)): op(f) { t.resize(2 * MAXN, e); }
  void update(int k, ll x) {
    for (t[k += MAXN] = x; (k /= 2) >= 1; t[k] = op(t[2 * k], t[2 * k + 1]));
  }
  ll query(int a, int b) {
    ll r = t[0];
    for (a += MAXN, b += MAXN; a <= b; ++a /= 2, --b /= 2) {
      if (a & 1) r = op(r, t[a]);
      if (~b & 1) r = op(r, t[b]);
    }
    return r;
  }
};

void solve() {
  int N; cin >> N;
  SegmentTree seg_v(0, [](ll x, ll y) { return x + y; }),
              seg_c(0, [](ll x, ll y) { return x + y; });
  ll ans = 0;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    ll sum = seg_v.query(x + 1, N), cnt = seg_c.query(x + 1, N);
    ll val = sum - cnt * x;
    ans = (ans + val) % MOD;
    seg_v.update(x, x); seg_c.update(x, 1);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
