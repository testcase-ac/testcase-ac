#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  int dold = abs(n - m), dnew, ans = 0;
  for (int a = n * m - 1; a >= 1; a--) {
    bool found = false;
    for (int j = 1; j * j <= a; j++) {
      if (a % j) continue;

      if (abs(abs(j - a / j) - dold) <= k) {
        found = true;
        break;
      }
    }

    if (found) ans++;
    else break;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
