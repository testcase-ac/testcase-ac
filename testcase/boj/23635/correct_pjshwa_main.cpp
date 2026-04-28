#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 202000;
ll a[MAX];

void solve() {
  int k, n;
  cin >> k >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (i > 0) a[i] += a[i - 1];
  }

  ll ans = 1e18;
  for (int mtake = 1; mtake <= 500000; mtake++) {
    vector<ll> values;
    ll prev = 0;
    for (int i = 0; i < k; i++) {
      auto it = lower_bound(a, a + n, prev + mtake);
      if (it == a + n) break;
      ll next = *it;
      values.push_back(next - prev);
      prev = next;
    }
    if (values.size() == k) {
      ll mvalue = *min_element(values.begin(), values.end());
      ll cur = 0;
      for (ll val : values) cur += val - mvalue;
      ans = min(ans, cur);
    }
    else break;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
