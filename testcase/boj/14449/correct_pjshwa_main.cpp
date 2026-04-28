#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;

struct SegmentTree {
  vector<ll> t; ll (*op)(ll,ll);
  SegmentTree(ll e, ll f(ll,ll)): op(f) {t.resize(2*MAX,e);}
  void update(int k, ll x) {
    for (t[k += MAX] = x; (k /= 2) >= 1; t[k] = op(t[2*k],t[2*k+1]));
  }
  ll query(int a, int b) {
    ll r = t[0];
    for (a += MAX, b += MAX; a <= b; ++a /= 2, --b /= 2) {
      if (a&1) r = op(r,t[a]);
      if (~b&1) r = op(r,t[b]);
    }
    return r;
  }
};

void compress(vector<int>& a) {
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
}

void solve() {
  int N; cin >> N;

  vector<int> A(N), B(N);
  for (int i = 0; i < N; i++) cin >> A[i], B[i] = A[i];
  compress(B);

  SegmentTree sl(0, [](ll x,ll y){return x+y;}),
              sr(0, [](ll x,ll y){return x+y;});

  for (int i = 0; i < N; i++) {
    int idx = lower_bound(B.begin(), B.end(), A[i]) - B.begin();
    sr.update(idx, sr.query(idx, idx) + 1);
  }

  int ans = 0;
  for (int i = 0; i < N; i++) {
    int idx = lower_bound(B.begin(), B.end(), A[i]) - B.begin();

    sr.update(idx, sr.query(idx, idx) - 1);

    int lc = sl.query(idx + 1, MAX - 1), rc = sr.query(idx + 1, MAX - 1);
    if (lc > 2 * rc || rc > 2 * lc) ans++;

    sl.update(idx, sl.query(idx, idx) + 1);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
