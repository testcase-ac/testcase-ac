#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
pii a[MAX];

void solve() {
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
  sort(a, a + n);
  
  while (q--) {
    int u, v, x, y;
    cin >> u >> v >> x >> y;

    int l = lower_bound(a, a + n, pii(u, -1)) - a;
    int ans = 0;
    for (int i = l; i < n && a[i].first <= v; i++) {
      if (x <= a[i].second && a[i].second <= y) ans++;
    }
    cout << ans << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
