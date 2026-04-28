#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int lcm(int a, int b) {
  return a / __gcd(a, b) * b;
}

void solve() {
  int p1, p2, p3, x1, x2, x3;
  cin >> p1 >> p2 >> p3 >> x1 >> x2 >> x3;

  int l = lcm(p1, lcm(p2, p3));
  for (int i = 1; i <= l; i++) {
    if (i % p1 == x1 && i % p2 == x2 && i % p3 == x3) {
      cout << i << '\n';
      return;
    }
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
