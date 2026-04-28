#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int x[11]{};
  for (int i = 0; i < 2047; i++) {
    for (int j = 0; j < 11; j++) {
      int a; cin >> a;
      x[j] ^= a;
    }
  }

  for (int j = 0; j < 11; j++) cout << x[j] << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
