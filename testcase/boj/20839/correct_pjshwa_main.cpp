#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int a, c, e, x, y, z;
  cin >> a >> c >> e >> x >> y >> z;

  if (c == y) {
    if (a == x) cout << "A\n";
    else if (2 * x >= a) cout << "B\n";
    else cout << "C\n";
  }
  else if (2 * y >= c) cout << "D\n";
  else cout << "E\n";
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
