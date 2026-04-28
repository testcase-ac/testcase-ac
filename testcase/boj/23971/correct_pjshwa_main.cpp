#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int h, w, n, m;
  cin >> h >> w >> n >> m;

  int z1 = (h - 1) / (n + 1) + 1, z2 = (w - 1) / (m + 1) + 1;
  cout << z1 * z2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
