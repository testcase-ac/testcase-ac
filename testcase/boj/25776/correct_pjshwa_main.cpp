#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, k;
  cin >> n >> k;

  int ans = 0;

  for (int state = 0; state < (1 << n); state++) {
    int streak = 0, l = -1, f = 0;
    for (int i = 0; i < n; i++) {
      if (state & (1 << i)) {
        if (l == 1) streak++;
        else streak = 1;
      }
      else {
        if (l == 0) streak++;
        else streak = 1;
      }
      if (streak > k) f = 1;
      l = (state & (1 << i)) ? 1 : 0;
    }
    if (!f) ans++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
