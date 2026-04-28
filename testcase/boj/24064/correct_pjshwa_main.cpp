#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int a;
  cin >> a;
  if (a < 0) cout << "1\n";
  else if (a == 1) cout << "INF\n";
  else cout << a << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
