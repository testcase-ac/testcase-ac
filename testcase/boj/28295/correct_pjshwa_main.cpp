#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int dir = 0;
  for (int i = 0; i < 10; i++) {
    int x; cin >> x;
    dir = (dir + x) % 4;
  }

  if (dir == 0) cout << "N\n";
  else if (dir == 1) cout << "E\n";
  else if (dir == 2) cout << "S\n";
  else cout << "W\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
