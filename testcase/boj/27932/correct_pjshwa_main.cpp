#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, k; cin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];

  int l = 0, r = 1e9;
  while (l < r) {
    int m = (l + r) / 2;

    int cnt = 0;
    for (int i = 0; i < n; i++) {
      int f = 0;
      for (int d : {-1, 1}) {
        int j = i + d;
        if (j < 0 || j >= n) continue;
        if (abs(a[i] - a[j]) > m) f = 1;
      }
      cnt += f;
    }

    if (cnt <= k) r = m;
    else l = m + 1;
  }

  cout << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
