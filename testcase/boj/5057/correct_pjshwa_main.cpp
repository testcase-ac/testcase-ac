#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, m;
  cin >> n >> m;
  n = abs(n), m = abs(m);
  if (n == 0 && m == 0) cout << "0\n";
  else if (__gcd(n, m) == 1) cout << "1\n";
  else cout << "2\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
