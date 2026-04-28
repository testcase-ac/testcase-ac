#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, m, k; cin >> n >> m >> k;

  int ans = k, dis = n + m;
  for (int i = 1; i <= k; i++) {
    int f, d; cin >> f >> d;
    int cur = (m - d) + (f - 1);
    if (dis > cur) dis = cur, ans = i;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
