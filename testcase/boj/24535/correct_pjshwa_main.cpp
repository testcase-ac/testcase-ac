#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;

  ll ans = 0, px = 0, py = 0;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    ans += px * y + py * x;
    px += x;
    py += y;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
