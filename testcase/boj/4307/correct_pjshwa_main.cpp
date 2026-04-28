#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int l, n;
  cin >> l >> n;

  int mn = 0, mx = 0;
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    mn = max(mn, min(x, l - x));
    mx = max(mx, max(x, l - x));
  }
  cout << mn << ' ' << mx << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
