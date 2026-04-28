#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;
  multiset<int> ma, mb, wa, wb;
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    if (x < 0) ma.insert(-x);
    else mb.insert(x);
  }
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    if (x < 0) wa.insert(-x);
    else wb.insert(x);
  }

  int ans = 0;
  for (int e : wb) {
    auto it = ma.upper_bound(e);
    if (it != ma.end()) {
      ans++;
      ma.erase(it);
    }
  }
  for (int e : mb) {
    auto it = wa.upper_bound(e);
    if (it != wa.end()) {
      ans++;
      wa.erase(it);
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
