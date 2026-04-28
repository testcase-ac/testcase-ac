#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int D[10] = {0, 1, 2, 2, 2, 3, 3, 3, 3, 3};

void solve() {
  ll n, k, x; cin >> n >> k >> x;
  ll ans = n - D[x] - 3 * k + 4;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
