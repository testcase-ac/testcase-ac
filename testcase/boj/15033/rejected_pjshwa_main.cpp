#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  vector<tuple<int, int, int, int, int, int>> ans;

  int xs1, ys1, zs1, xe1, ye1, ze1; cin >> xs1 >> ys1 >> zs1 >> xe1 >> ye1 >> ze1;
  int xs2, ys2, zs2, xe2, ye2, ze2; cin >> xs2 >> ys2 >> zs2 >> xe2 >> ye2 >> ze2;

  int xc1 = xs1, yc1 = ys1, zc1 = zs1, xc2 = xs2, yc2 = ys2, zc2 = zs2;

  auto move = [&]() {
    int nxc1 = xc1, nyc1 = yc1, nzc1 = zc1, nxc2 = xc2, nyc2 = yc2, nzc2 = zc2;

    int x1dir = xe1 > xc1 ? 1 : -1, x1move = abs(xe1 - xc1);
    int y1dir = ye1 > yc1 ? 1 : -1, y1move = abs(ye1 - yc1);
    int z1dir = ze1 > zc1 ? 1 : -1, z1move = abs(ze1 - zc1);
    int x2dir = xe2 > xc2 ? 1 : -1, x2move = abs(xe2 - xc2);
    int y2dir = ye2 > yc2 ? 1 : -1, y2move = abs(ye2 - yc2);
    int z2dir = ze2 > zc2 ? 1 : -1, z2move = abs(ze2 - zc2);

    if (x1move) nxc1 += x1dir;
    else if (y1move) nyc1 += y1dir;
    else if (z1move) nzc1 += z1dir;

    if (x2move) nxc2 += x2dir;
    else if (y2move) nyc2 += y2dir;
    else if (z2move) nzc2 += z2dir;

    // if collide, don't move robot 2 for now
    bool collide = (nxc1 == nxc2 && nyc1 == nyc2 && nzc1 == nzc2);
    collide |= (
      nxc1 == xc2 && nyc1 == yc2 && nzc1 == zc2 &&
      nxc2 == xc1 && nyc2 == yc1 && nzc2 == zc1
    );

    if (collide) {
      do {
        nxc1 = xc1, nyc1 = yc1, nzc1 = zc1;

        // random move
        int dir = rand() % 6;
        if (dir % 3 == 0) nxc1 = dir >= 3 ? xc1 + 1 : xc1 - 1;
        else if (dir % 3 == 1) nyc1 = dir >= 3 ? yc1 + 1 : yc1 - 1;
        else nzc1 = dir >= 3 ? zc1 + 1 : zc1 - 1;
      } while (nxc1 == xc2 && nyc1 == yc2 && nzc1 == zc2);
      xc1 = nxc1, yc1 = nyc1, zc1 = nzc1;
    }
    else xc1 = nxc1, yc1 = nyc1, zc1 = nzc1, xc2 = nxc2, yc2 = nyc2, zc2 = nzc2;
  };

  ans.emplace_back(xc1, yc1, zc1, xc2, yc2, zc2);
  while (xc1 != xe1 || yc1 != ye1 || zc1 != ze1 || xc2 != xe2 || yc2 != ye2 || zc2 != ze2) {
    move();
    ans.emplace_back(xc1, yc1, zc1, xc2, yc2, zc2);
  }

  for (auto [x1, y1, z1, x2, y2, z2] : ans) {
    cout << x1 << " " << y1 << " " << z1 << " " << x2 << " " << y2 << " " << z2 << "\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
