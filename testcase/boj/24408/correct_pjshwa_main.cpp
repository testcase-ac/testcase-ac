#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int get() {
  int x;
  if (cin >> x) return x;
  else exit(0);
}

void solve() {
  int x, y;
  cin >> x;
  x = get();
  while (1) {
    y = get();
    if (y % x == 0) {
      cout << y << '\n';
      x = get();
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
