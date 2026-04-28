#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll upto(ll n) {
  ll l = n, ret = 0;
  if (n <= 10) {
    for (ll i = 1; i <= n; ++i) {
      ret ^= i;
    }
    return ret;
  }
  while (l % 4 != 3) --l;
  for (ll i = l + 1; i <= n; ++i) {
    ret ^= i;
  }
  return ret;
}

void solve() {
  int N; cin >> N; ll ans = 0;
  for (int i = 0; i < N; ++i) {
    ll x, m; cin >> x >> m;
    ans ^= upto(x + m - 1);
    ans ^= upto(x - 1);
  }

  if (ans == 0) cout << "cubelover\n";
  else cout << "koosaga\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
