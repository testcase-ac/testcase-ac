#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int s, n;
  cin >> s >> n;
  vector<int> u(n + 1);
  for (int i = 0; i < n; i++) cin >> u[i];
  u[n] = u[0] + s;

  int ans = 0;
  for (int i = 0; i < n; i++) {
    ans += (u[i + 1] - u[i]) / 2 - 1;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
