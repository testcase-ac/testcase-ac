#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int a[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  ll sum = accumulate(a, a + n, 0LL);
  ll mxv = *max_element(a, a + n);
  if (sum > 2 * mxv) cout << sum / 2 << '\n';
  else cout << sum - mxv << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
