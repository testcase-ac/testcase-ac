#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int Sx, Sy, Ex, Ey, Px, Py; cin >> Sx >> Sy >> Ex >> Ey >> Px >> Py;
  if (Sx == Ex || Sy == Ey) {
    int minx = min(Sx, Ex), maxx = max(Sx, Ex);
    int miny = min(Sy, Ey), maxy = max(Sy, Ey);
    if (minx <= Px && Px <= maxx && miny <= Py && Py <= maxy) cout << "2\n";
    else cout << "0\n";
  }
  else cout << "1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
