#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int k;
void build(int a, int b, int c, int d, int n) {
  int x = a + c, y = b + d;
  if (y <= n) {
    build(a, b, x, y, n);
    build(x, y, c, d, n);
  }
  else {
    --k;
    if (k == 0) {
      cout << a << ' ' << b << '\n';
      exit(0);
    }
  }
}

void solve() {
  int n; cin >> n >> k;
  build(0, 1, 1, 0, n);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
