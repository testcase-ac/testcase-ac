#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int lcm(int a, int b) {
  return a / __gcd(a, b) * b;
}

void solve() {
  int a, b, s;
  cin >> a >> b >> s;
  if (lcm(a, b) <= s) cout << "yes\n";
  else cout << "no\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
