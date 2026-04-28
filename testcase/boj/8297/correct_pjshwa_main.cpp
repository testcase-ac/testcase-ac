#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, t;
  cin >> n >> t;

  vector<ll> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];

  if (n == 1) return cout << a[0] * (1 + t / 2) << '\n', void();

  t++;
  ll acc = 0, ans = 0;
  for (int i = 0; i < min(n - 1, t); i++) {
    int rem = t - i;

    ll cur = (a[i] + a[i + 1]) * (rem / 2);
    if (rem & 1) cur += a[i];
    ans = max(ans, cur + acc);

    acc += a[i];
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
