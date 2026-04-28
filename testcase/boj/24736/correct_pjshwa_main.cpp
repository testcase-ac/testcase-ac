#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  for (int i = 0; i < 2; i++) {
    int a, b, c, d, e;
    cin >> a >> b >> c >> d >> e;
    cout << 6 * a + 3 * b + 2 * c + d + 2 * e << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
