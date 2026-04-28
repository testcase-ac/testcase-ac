#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int dx[2] = {-1, 1};

void solve() {
  int n; cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    for (int d = 0; d < 2; d++) {
      int j = i + dx[d];
      if (j < 0 || j >= n) continue;
      ans += max(a[i], a[j]);
    }
  }
  cout << ans / 2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
