#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, k;
  cin >> n;
  vector<ll> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 1; i < n; i++) a[i] += a[i - 1];
  cin >> k;
  k++;

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    auto it = lower_bound(a.begin(), a.end(), i == 0 ? k : a[i - 1] + k);
    ans += n - (it - a.begin());
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
