#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, o, x, ans = 0;
  cin >> n >> o;

  for (int i = 0; i < n; i++) {
    cin >> x;
    if (x >= o) ans += min(x - o, o + 360 - x);
    else ans += min(o - x, x + 360 - o);
    o = x;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
