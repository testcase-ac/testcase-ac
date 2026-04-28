#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  ll p = N - 1, d = N / 2;
  for (ll i = 1; i < d; i++) {
    ll r = d * d - i * i;
    ll q = sqrt(r);
    if (q * q == r) p--;
  }
  cout << 4 * p << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
