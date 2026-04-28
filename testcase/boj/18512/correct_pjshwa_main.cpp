#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int x, y, p1, p2;
  cin >> x >> y >> p1 >> p2;

  if (__gcd(x, y) != __gcd(p1, p2)) return cout << "-1\n", void();
  
  while (p1 != p2) {
    if (p1 < p2) p1 += x;
    else p2 += y;
  }

  cout << p1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
