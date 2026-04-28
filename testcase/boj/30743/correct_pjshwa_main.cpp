#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

// What value appears on index i after shuffle?
ll f(ll n, ll i, int o) {
  if (o) {
    if (i & 1) {
      ll h = n / 2;
      return h + f(n - h, (i + 1) / 2, 1 - (n & 1));
    }
    else return i / 2;
  }
  else {
    if (i & 1) return (i + 1) / 2;
    else {
      ll h = (n + 1) / 2;
      return h + f(n - h, i / 2, n & 1);
    }
  }
}

void solve() {
  ll n; int q; cin >> n >> q;
  while (q--) {
    ll x; cin >> x;
    cout << f(n, x, 0) << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
