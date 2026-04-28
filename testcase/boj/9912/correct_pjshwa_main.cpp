#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n; cin >> n;

  int U[n]{}; ll v = 1;
  for (int i = 1; i <= n - 1; i++) v *= i;

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;

    for (int j = 0; j < x; j++) {
      if (U[j]) continue;
      else ans += v;
    }

    U[x] = 1;
    if (i < n - 1) v /= n - i - 1;
  }
  cout << ans + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
