#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int a, b, c, d; cin >> a >> b >> c >> d;
  if (a * b > c * d) cout << "M\n";
  else if (a * b < c * d) cout << "P\n";
  else cout << "E\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
