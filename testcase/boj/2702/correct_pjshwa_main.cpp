#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int lcm(int a, int b) {
  return a / __gcd(a, b) * b;
}

void solve() {
  int a, b;
  cin >> a >> b;
  cout << lcm(a, b) << ' ' << __gcd(a, b) << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
