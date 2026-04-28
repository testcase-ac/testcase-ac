#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int d[MAX];

void solve() {
  int n; cin >> n;
  for (int i = 0; i < n; ++i) cin >> d[i];
  sort(d, d + n, greater<int>());

  ll ans = 2 * d[0];
  for (int i = 1; i < n - 1; ++i) ans += d[i];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
