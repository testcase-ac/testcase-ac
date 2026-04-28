#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, l, r;
  cin >> n >> l >> r;

  for (int i = 3; i <= n; i++) {
    int x;
    cin >> x;
    if (l <= r) l += x;
    else r += x;
  }

  int need = abs(l - r), ans = 0;
  for (int w : {100, 50, 20, 10, 5, 2, 1}) {
    while (need >= w) {
      need -= w;
      ans++;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
