#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll x;
  cin >> x;
  ll q = sqrt(x);
  cout << (q * q == x) << ' ';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
