#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int a, b, c, d, e; cin >> a >> b >> c >> d >> e;

  int A = a * d * d - a * d;
  int B = 2 * a * d * e;
  int C = a * e * e + b * e + c - c * d - e;

  if (A == 0) {
    if (B == 0) {
      if (C == 0) cout << "Nice\n";
      else cout << "Head on\n";
    }
    else cout << "Remember my character\n";
  }
  else {
    int det = B * B - 4 * A * C;
    if (det > 0) cout << "Go ahead\n";
    else if (det == 0) cout << "Remember my character\n";
    else cout << "Head on\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
