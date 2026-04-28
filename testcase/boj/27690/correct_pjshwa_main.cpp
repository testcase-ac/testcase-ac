#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
ll d[MAX + 1];

ll r(ll n) {
  if (n == 1) return d[n] = 0;

  ll ret;
  if (n % 3 == 0) {
    ret = r(n / 3) + r(2 * n / 3) + (n / 3) * (2 * n / 3);
  }
  else if (n % 2 == 0) {
    ret = 2 * r(n / 2) + (n / 2) * (n / 2);
  }
  else {
    ret = r(n - 1) + r(1) + (n - 1);
  }
  return d[n] = ret;
}

void solve() {
  int n; cin >> n;
  cout << r(n) << '\n';
}

int main() {
  fast_io();

  memset(d, -1, sizeof(d));
  int t = 1;
  cin >> t;
  while (t--) solve();
}
