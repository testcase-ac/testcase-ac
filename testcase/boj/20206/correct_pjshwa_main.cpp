#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll A, B, C, x1, x2, y1, y2; cin >> A >> B >> C >> x1 >> x2 >> y1 >> y2;

  ll v1, v2;
  if (A == 0) v1 = B * y1 + C, v2 = B * y2 + C;
  else if (B == 0) v1 = A * x1 + C, v2 = A * x2 + C;
  else if (A * B > 0) v1 = A * x1 + B * y1 + C, v2 = A * x2 + B * y2 + C;
  else v1 = A * x1 + B * y2 + C, v2 = A * x2 + B * y1 + C;

  if (v1 * v2 < 0) cout << "Poor\n";
  else cout << "Lucky\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
