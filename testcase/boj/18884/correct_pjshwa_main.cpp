#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, m; cin >> n >> m;
  vector<string> s(n), t(m);
  for (auto& x : s) cin >> x;
  for (auto& x : t) cin >> x;

  int q; cin >> q;
  while (q--) {
    int y; cin >> y; y--;
    cout << (s[y % n] + t[y % m]) << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
