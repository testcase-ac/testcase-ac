#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXL = 2000;

void solve() {
  int W; cin >> W;

  for (int l = 1; l <= MAXL; ++l) {
    if (2 * l * l == W) return cout << 8 * l << '\n', void();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
