#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

map<ll, ll> d;
ll r(ll n) {
  if (n == 1) return 0;
  if (d.count(n)) return d[n];

  ll x = n / 2, y = n - x;
  ll ret = r(x) + r(y) + x * y;
  return d[n] = ret;
}

void solve() {
  int n; cin >> n;
  cout << r(n) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
