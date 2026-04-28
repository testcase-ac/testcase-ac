#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;

  vector<int> v54;
  for (ll val5 = 1;; val5++) {
    ll val = 1;
    for (int i = 0; i < 5; i++) val *= val5;
    if (val > n) break;

    for (ll val4 = 1;; val4++) {
      ll add1 = 1;
      for (int i = 0; i < 4; i++) add1 *= val4;
      if (val + add1 > n) break;
      
      v54.push_back(val + add1);

    }
  }
  sort(v54.begin(), v54.end());

  ll ans = 0;
  for (ll val3 = 1;; val3++) {
    ll val = 1;
    for (int i = 0; i < 3; i++) val *= val3;
    if (val > n) break;

    for (ll val2 = 1;; val2++) {
      ll add = val2 * val2;
      if (val + add <= n) {
        auto it = lower_bound(v54.begin(), v54.end(), n - val - add);
        ans += (it - v54.begin());
      }
      else break;
    }

  }
  cout << ans << endl;
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
