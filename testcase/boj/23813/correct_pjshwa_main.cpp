#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string ns;
  cin >> ns;

  int sz = ns.size();
  ll ans = 0;
  for (int i = 0; i < sz; i++) {
    ns = ns.substr(1) + ns[0];
    ans += stoll(ns);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
