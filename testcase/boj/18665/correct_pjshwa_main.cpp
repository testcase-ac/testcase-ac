#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

set<ll> u;

void r(ll n) {
  if (u.count(n)) return;

  ll q = sqrt(n);
  if (q * q == n) {
    r(q);
    cout << q << " 0\n";
  }
  else {
    q++;
    r(q);
    r(q * q - n);
    cout << q << ' ' << q * q - n << '\n';
  }
  u.insert(n);
}

void solve() {
  ll n;
  cin >> n;

  for (int i = 0; i < 3; i++) u.insert(i);
  r(n);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
