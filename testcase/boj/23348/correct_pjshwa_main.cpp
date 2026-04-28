#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int a, b, c, n, mx = 0;
  cin >> a >> b >> c >> n;
  assert(0 <= a && a <= 1000);
  assert(0 <= b && b <= 1000);
  assert(0 <= c && c <= 1000);
  assert(1 <= n && n <= 1000);

  for (int i = 0; i < n; i++) {
    int cx = 0;
    for (int t = 0; t < 3; t++) {
      int x, y, z;
      cin >> x >> y >> z;
      assert(0 <= x && x <= 100);
      assert(0 <= y && y <= 100);
      assert(0 <= z && z <= 100);
      cx += x * a + y * b + z * c;
    }
    assert(0 <= cx && cx <= 900000);
    mx = max(mx, cx);
  }

  cout << mx << '\n';
}
