#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, m, q;
  cin >> n >> m >> q;

  int xl = 1, xu = n, yl = 1, yu = m;
  while (q--) {
    int xi, yi, di;
    cin >> xi >> yi >> di;
    if (di == 1) xl = max(xl, xi + 1), yl = max(yl, yi), yu = min(yu, yi);
    if (di == 2) xu = min(xu, xi - 1), yl = max(yl, yi), yu = min(yu, yi);
    if (di == 3) yu = min(yu, yi - 1), xl = max(xl, xi), xu = min(xu, xi);
    if (di == 4) yl = max(yl, yi + 1), xl = max(xl, xi), xu = min(xu, xi);
    if (di == 5) xl = max(xl, xi + 1), yl = max(yl, yi + 1);
    if (di == 6) xu = min(xu, xi - 1), yl = max(yl, yi + 1);
    if (di == 7) xl = max(xl, xi + 1), yu = min(yu, yi - 1);
    if (di == 8) xu = min(xu, xi - 1), yu = min(yu, yi - 1);
    if (di == 9) xl = max(xl, xi), xu = min(xu, xi), yl = max(yl, yi), yu = min(yu, yi);
  }

  ll nside = xu - xl + 1, mside = yu - yl + 1;
  cout << nside * mside << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
