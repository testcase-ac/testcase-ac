#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int inv[MAX + 1];

struct SegmentTree {
  ll t[2*MAX]; ll (*op)(ll,ll);
  SegmentTree(ll e, ll f(ll,ll)): op(f) { fill(t,t+2*MAX,e); }
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

SegmentTree rsq(0, [](ll x,ll y){return x+y;});

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    inv[x] = i;
  }

  ll ans = 0;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    ans += rsq.query(inv[x], N - 1);
    rsq.update(inv[x], 1);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
