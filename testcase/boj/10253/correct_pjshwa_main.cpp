#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void r(int a, int b) {
  if (a == 1) cout << b << '\n';
  else {
    int s = (b - 1) / a + 1;
    int na = a * s - b, nb = b * s;
    int g = __gcd(na, nb);
    r(na / g, nb / g);
  }
}

void solve() {
  int a, b;
  cin >> a >> b;
  r(a, b);
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
