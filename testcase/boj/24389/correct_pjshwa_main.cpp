#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

unsigned int mask = (1 << 32) - 1;

void solve() {
  unsigned int n;
  cin >> n;

  auto v = (n ^ mask) + 1;
  cout << __builtin_popcount(v ^ n) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
