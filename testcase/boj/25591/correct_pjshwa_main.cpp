#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int x, y;
  cin >> x >> y;

  int a = 100 - x, b = 100 - y;
  int c = 100 - (a + b);
  int d = a * b;

  int q = d / 100, r = d % 100;

  cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << q << ' ' << r << '\n';
  cout << c + q << ' ' << r << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
