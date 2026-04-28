#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
ll X, N, P[MAXN + 1];

ll do_pass(ll x) {
  for (int i = 0; i < N; ++i) {
    x += P[i];
    x = min(x, X); x = max(x, 0LL);
  }
  return x;
}

void solve() {
  cin >> X >> N;
  for (int i = 0; i < N; ++i) cin >> P[i];

  ll s = do_pass(0), e = do_pass(X), i1, i2;
  {
    ll l = 0, r = X + 1;
    while (l < r) {
      ll m = (l + r) / 2;
      if (do_pass(m) == s) l = m + 1;
      else r = m;
    }
    i1 = l - 1;
  }
  {
    ll l = 0, r = X + 1;
    while (l < r) {
      ll m = (l + r) / 2;
      if (do_pass(m) == e) r = m;
      else l = m + 1;
    }
    i2 = l;
  }

  ll Q, x; cin >> Q;
  while (Q--) {
    cin >> x;
    if (x <= i1) cout << s << '\n';
    else if (x >= i2) cout << e << '\n';
    else cout << s + x - i1 << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
