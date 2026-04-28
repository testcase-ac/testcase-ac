#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int P, M, F, C; cin >> P >> M >> F >> C;
  int wins = M / P, coupons = wins * C;

  int F1 = coupons / F, F2 = 0;
  if (coupons >= F) F2 = 1 + (coupons - F) / (F - C);
  cout << F2 - F1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
