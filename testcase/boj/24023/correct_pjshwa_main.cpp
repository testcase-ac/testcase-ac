#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, k;
  cin >> n >> k;

  int x = 0, s = 1;
  for (int i = 1, u; i <= n; i++) {
    cin >> u;
    x |= u;

    if ((k & x) == x) {
      if (x == k) return cout << s << ' ' << i << '\n', void();
    }
    else x = 0, s = i + 1;
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
