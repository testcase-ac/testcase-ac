#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
ull a[MAX];

void solve() {
  int m, n;
  cin >> m >> n;

  ull sum = 0;
  for (int i = 0; i < n; i++) cin >> a[i], sum += a[i];
  sort(a, a + n);

  ull diff = sum - m, ans = 0;
  for (int i = 0; i < n; i++) {
    ull dec = min(diff / (n - i), a[i]);
    diff -= dec;
    ans += dec * dec;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
