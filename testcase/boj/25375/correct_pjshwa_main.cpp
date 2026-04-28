#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll a, b;
  cin >> a >> b;
  if (b % a) return cout << "0\n", void();
  b /= a;
  cout << (b >= 2) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
