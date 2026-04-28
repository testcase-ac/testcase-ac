#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll k, a, b, c, d;
  cin >> k >> a >> b >> c >> d;

  if (a * k + b == c * k + d) cout << "Yes " << a * k + b << '\n';
  else cout << "No\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
