#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int a, b, c;
  cin >> a >> b >> c;

  int ans = 0;
  for (int x = 1; x <= a; x++) for (int y = 1; y <= b; y++) for (int z = 1; z <= c; z++) {
    if (x % y == y % z && y % z == z % x) ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
