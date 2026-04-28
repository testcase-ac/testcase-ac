#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int m, n;
  cin >> m >> n;

  map<vector<int>, int> c;
  for (int i = 0; i < m; i++) {
    vector<int> u(n);
    vector<pii> a(n);

    for (int j = 0, x; j < n; j++) {
      cin >> x;
      a[j] = {x, j};
    }
    sort(a.begin(), a.end());

    int last = -1;
    for (int j = 0, ord = 0; j < n; j++) {
      auto [val, idx] = a[j];
      if (val != last) ord++;
      u[idx] = ord;
      last = val;
    }
    
    c[u]++;
  }

  int ans = 0;
  for (auto& [k, v] : c) ans += v * (v - 1) / 2;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
