#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, m; cin >> n >> m;

  cout << "YES\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i == n - 1) cout << '0';
      else if (i == n - 2 || j % 2 == 1) cout << '1';
      else cout << '0';
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
