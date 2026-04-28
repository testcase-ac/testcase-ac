#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int a[MAX];

void solve() {
  int n, m;
  cin >> n >> m;

  vector<int> b(m);
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < m; i++) cin >> b[i];
  sort(b.begin(), b.end());

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    auto it = lower_bound(b.begin(), b.end(), a[i]);
    if (it == b.begin()) ans += *it;
    else if (it == b.end()) ans += *(it - 1);
    else {
      ll rdiff = *it - a[i];
      ll ldiff = a[i] - *(it - 1);

      if (ldiff <= rdiff) ans += *(it - 1);
      else ans += *it;
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
