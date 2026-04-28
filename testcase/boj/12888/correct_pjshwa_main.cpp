#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll N;
  cin >> N;

  vector<ll> d(61);
  d[0] = 1;
  for (int i = 1; i <= 60; i++) {
    d[i] = 2 * d[i - 1] + ((i & 1) ? -1 : 1);
  }

  cout << d[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
