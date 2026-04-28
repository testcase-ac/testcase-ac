#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, MAXD = 365;
pii a[MAX]; int C[MAXD + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
  sort(a, a + n, [] (pii a, pii b) {
    if (a.first == b.first) return a.second > b.second;
    return a.first < b.first;
  });

  for (int i = 0; i < n; i++) {
    auto [s, e] = a[i];
    for (int j = s; j <= e; j++) C[j]++;
  }

  int ans = 0, streak = 0, xdepth = 0;
  for (int i = 1; i <= MAXD; i++) {
    if (C[i] == 0) {
      ans += streak * xdepth;
      streak = xdepth = 0;
    }
    else {
      streak++;
      xdepth = max(xdepth, C[i]);
    }
  }
  ans += streak * xdepth;

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
