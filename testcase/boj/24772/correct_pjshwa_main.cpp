#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int r, h, s;

void solve() {
  double ans = 2 * sqrt(h * h - r * r) + (2 * M_PI - 2 * acos((double)r / h)) * r;
  cout << fixed << setprecision(2) << ans * (100.0 + s) / 100.0 << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> r >> h >> s;
    if (r == 0 && h == 0 && s == 0) break;
    solve();
  }
}
