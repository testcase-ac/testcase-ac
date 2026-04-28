#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50001;

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
  int N; cin >> N;
  vector<pii> A;
  for (int i = 0; i < N; i++) {
    int v, x; cin >> v >> x;
    A.push_back({v, x});
  }
  sort(A.begin(), A.end());

  SegmentTree S(0, [](ll x, ll y) { return x + y; });
  SegmentTree C(0, [](ll x, ll y) { return x + y; });

  ll ans = 0;
  for (auto& [v, x] : A) {
    ll lcnt = C.query(0, x - 1), rcnt = C.query(x + 1, MAX);
    ll tdis = (lcnt * x) - S.query(0, x - 1) + S.query(x + 1, MAX) - (rcnt * x);
    ans += tdis * v;

    C.update(x, C.query(x, x) + 1);
    S.update(x, S.query(x, x) + x);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
