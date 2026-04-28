#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int x, y;
  cin >> x >> y;

  vector<int> sx, sy;
  while (x) sx.push_back(x % 3), x /= 3;
  while (y) sy.push_back(y % 3), y /= 3;
  while (sx.size() < sy.size()) sx.push_back(0);
  while (sy.size() < sx.size()) sy.push_back(0);
  reverse(sx.begin(), sx.end());
  reverse(sy.begin(), sy.end());

  for (int i = 0; i < sx.size(); i++) {
    if (sx[i] == 1 && sy[i] == 0) continue;
    if (sx[i] == 0 && sy[i] == 1) continue;
    return cout << "0\n", void();
  }

  cout << "1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
