#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int X, Y; cin >> X >> Y;

  int l = X * Y;
  for (int i = 1; i <= l; ++i) {
    if (i % X == 0) {
      if (i % Y == 0) cout << '3';
      else cout << '2';
    }
    else if (i % Y == 0) cout << '1';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
