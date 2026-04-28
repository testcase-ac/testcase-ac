#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int m, d;
  cin >> m >> d;
  if (m < 2) cout << "Before\n";
  else if (m > 2) cout << "After\n";
  else {
    if (d < 18) cout << "Before\n";
    else if (d > 18) cout << "After\n";
    else cout << "Special\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
