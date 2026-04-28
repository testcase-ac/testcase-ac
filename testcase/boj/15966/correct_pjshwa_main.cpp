#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;

  map<int, int> d;
  int x, ans = 0;
  for (int i = 0; i < n; i++) {
    cin >> x;
    d[x] = max(d[x], d[x - 1] + 1);
    ans = max(ans, d[x]);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
