#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n = 4;
  cin >> n;

  int p[n];
  for (int i = 0; i < n; ++i) p[i] = i;

  int u[n];
  for (int i = 0; i < n; ++i) cin >> u[i];

  int ans = 0;
  do {
    bool f = true;
    for (int i = 0; i < n; i++) {
      if (u[p[i]] == 1 && i <= p[i]) {
        f = false;
        break;
      }
      if (u[p[i]] == -1 && i >= p[i]) {
        f = false;
        break;
      }

    }
    if (f) ans++;

  } while (next_permutation(p, p + n));

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
