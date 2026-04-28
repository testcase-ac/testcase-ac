#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX];

void solve() {
  int n, k, t;
  cin >> n >> k >> t;

  ll sum = 0;
  for (int i = 0; i < n; i++) cin >> a[i], sum += a[i];

  if (sum % k) return cout << "NO\n", void();

  ll rsum = 0;
  vector<int> o;
  for (int i = 0; i < n; i++) {
    if (a[i] == 0) continue;
    rsum += (k - a[i]);
    o.push_back(a[i]);
  }
  sort(o.begin(), o.end());

  if (rsum == 0) return cout << "YES\n", void();

  ll op = 0;
  for (int oe : o) {
    rsum -= (k - oe);
    op += oe;
    if (rsum == op && op <= t) return cout << "YES\n", void();
  }

  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
