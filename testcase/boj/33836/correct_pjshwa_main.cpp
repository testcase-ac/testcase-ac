#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int x, y; cin >> x >> y;
  if (y == 0) {
    if (x >= 0) cout << "0\n";
    else cout << "1\n";
  }
  else {
    if (y > 0) {
      if (x >= 0) cout << "1\n";
      else cout << "2\n";
    }
    else {
      if (x >= y) cout << "1\n";
      else cout << "2\n";
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
