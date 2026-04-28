#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const ll MOD = 1e18;
const double PI = acos(-1);

map<double, ll> d;
ll r(double n) {
  if (d.count(n)) return d[n];
  if (n <= PI) return d[n] = 1;

  return d[n] = (r(n - 1) + r(n - PI)) % MOD;
}

void solve() {
  int n;
  cin >> n;
  cout << r(n) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
