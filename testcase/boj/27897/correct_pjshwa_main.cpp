#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5 + 10;

struct SegmentTree {
  vector<ll> t; ll (*op)(ll, ll);
  SegmentTree(ll e, ll f(ll, ll)): op(f) { t.resize(2 * MAX, e); }
  void update(int k, ll x) {
    for (t[k += MAX] = x; (k /= 2) >= 1; t[k] = op(t[2 * k], t[2 * k + 1]));
  }
  ll query(int a, int b) {
    ll r = t[0];
    for (a += MAX, b += MAX; a <= b; ++a /= 2, --b /= 2) {
      if (a & 1) r = op(r, t[a]);
      if (~b & 1) r = op(r, t[b]);
    }
    return r;
  }
};

void solve() {
  ll N, L; cin >> N >> L;

  SegmentTree s(0, [](ll x, ll y) { return x + y; });

  ll ans = 0;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    ans += s.query(x + 1, N);
    s.update(x, 1);
  }
  ans = min(ans + L, N * (N - 1) / 2);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
