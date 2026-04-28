#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int ans = 0;
  for (int i = 0; i < 4; i++) {
    string u; int x; cin >> u >> x;
    if (u == "Es") ans += 21 * x;
    else ans += 17 * x;
  }
  cout << ans << '\n';
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
