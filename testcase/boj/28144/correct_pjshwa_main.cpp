#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll n, d; cin >> n >> d;

  __int128_t v = 1; int res = 0;
  while (v < n) v *= (d + 1), res++;
  cout << res << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
