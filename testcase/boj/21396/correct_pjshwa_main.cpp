#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX];

void solve() {
  int n, x;
  cin >> n >> x;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    auto [l, r] = equal_range(a + i + 1, a + n, x ^ a[i]);
    ans += (r - l);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
