#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, d, x;
  cin >> n >> d >> x;

  set<int> s{x};
  cout << x << ' ';
  for (int i = 2; i <= n; i++) {
    cin >> x;

    int cur = x;
    while (s.upper_bound(cur - d) != s.upper_bound(cur + d - 1)) {
      cur = *s.upper_bound(cur - d) + d;
    }

    cout << cur << ' ';
    s.insert(cur);
  }

  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
