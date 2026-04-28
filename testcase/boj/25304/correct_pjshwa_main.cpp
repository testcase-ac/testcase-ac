#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll x, n;
  cin >> x >> n;

  ll s = 0;
  for (int i = 0; i < n; i++) {
    ll a, b;
    cin >> a >> b;
    s += a * b;
  }

  if (x == s) cout << "Yes\n";
  else cout << "No\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
