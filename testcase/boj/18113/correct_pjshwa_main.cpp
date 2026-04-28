#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, k, m;
  cin >> n >> k >> m;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];

  int left = 1, right = 1e9 + 1, ans = -1;
  while (left < right) {
    int mid = (left + right) / 2;

    int cnt = 0;
    for (int i = 0; i < n; i++) {
      int v;
      if (a[i] <= k) continue;

      if (a[i] < 2 * k) v = a[i] - k;
      else v = a[i] - 2 * k;

      cnt += v / mid;
    }

    if (cnt < m) right = mid;
    else ans = mid, left = mid + 1;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
