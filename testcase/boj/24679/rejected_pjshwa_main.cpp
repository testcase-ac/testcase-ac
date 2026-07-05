#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 30;
int d[MAX + 10][MAX + 10][MAX + 10];

bool r(int x, int y, int z) {
  if (d[x][y][z] != -1) return d[x][y][z];

  if (x == 0 && y == 0) return d[x][y][z] = true;
  if (x == 0 && z == 0) return d[x][y][z] = true;
  if (y == 0 && z == 0) return d[x][y][z] = true;

  bool res = false;
  if (x == 0) res = !r(x, y - 1, z - 1);
  else if (y == 0) res = !r(x - 1, y, z - 1);
  else if (z == 0) res = !r(x - 1, y - 1, z);
  else {
    res |= !r(x - 1, y - 1, z);
    res |= !r(x - 1, y, z - 1);
    res |= !r(x, y - 1, z - 1);
  }
  return d[x][y][z] = res;
}

void solve() {
  for (int x = 1; x <= MAX; x++) {
    for (int y = x; y <= MAX; y++) {
      for (int z = y; z <= MAX; z++) {
        // if (r(x, y, z)) continue;
        cout << "x: " << x << ", y: " << y << ", z: " << z << ", res: " << r(x, y, z) << '\n';
      }
    }
  }

  // int x[3];
  // cin >> x[0] >> x[1] >> x[2];
  // sort(x, x + 3);

  // int ocnt = 0;
  // if (x & 1) ocnt++;
  // if (y & 1) ocnt++;
  // if (z & 1) ocnt++;
  // cout << (ocnt > 1 ? "B" : "R") << '\n';
}

int main() {
  fast_io();

  memset(d, -1, sizeof(d));

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
