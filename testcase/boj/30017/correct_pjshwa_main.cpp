#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int A, B; cin >> A >> B;

  int ans = 3;
  for (int Y = 1; Y <= B; ++Y) {
    if (A >= Y + 1) ans = max(ans, 2 * Y + 1);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
