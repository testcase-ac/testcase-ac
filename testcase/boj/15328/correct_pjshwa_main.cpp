#include <bits/stdc++.h>
#define ff __float128
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ff fsqrt(ff num) {
  ff temp, val;
  val = num / 2;
  temp = 0;

  // It will stop only when temp is the square of our number
  while (val != temp) {

    // setting sqrt as temp to save the value for modifications
    temp = val;

    // main logic for square root of any number (Non Negative)
    val = (num / temp + temp) / 2;
  }
  
  return val;
}

ff dist(ff cx, ff cy, ff cz, ff nx, ff ny, ff nz) {
  return fsqrt(
    (nx - cx) * (nx - cx) + (ny - cy) * (ny - cy) + (nz - cz) * (nz - cz)
  );
}

int main() {
  fast_io();

  int t, x;
  ff cx, cy, cz;
  int nx, ny, nz;
  cin >> t;
  while (t--) {
    cin >> x;
    cx = 0, cy = 0, cz = 0;

    int r = 4;
    ff ans = 0;
    while (r--) {
      cin >> nx >> ny >> nz;
      ans += dist(cx, cy, cz, nx, ny, nz);
      cx = nx, cy = ny, cz = nz;
    }

    cout << (ans <= x ? "YES" : "NO") << '\n';
  }

}
