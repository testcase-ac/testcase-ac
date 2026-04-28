#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, m, ans = 0;
  cin >> n >> m;
  map<int, int> u;
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    u[x] ^= 1;
  }
  for (int i = 0, x; i < m; i++) {
    cin >> x;
    u[x] ^= 1;
  }
  for (auto &[k, v] : u) {
    if (v) ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
