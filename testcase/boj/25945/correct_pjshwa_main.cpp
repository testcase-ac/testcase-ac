#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  sort(a.begin(), a.end());

  int sum = accumulate(a.begin(), a.end(), 0);
  vector<int> b(n, sum / n);
  int rem = sum % n;
  for (int i = 0; i < rem; ++i) b[n - 1 - i]++;

  ll ans = 0;
  for (int i = 0; i < n; ++i) ans += abs(a[i] - b[i]);
  cout << ans / 2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
