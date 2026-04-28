#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX], d[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i] >> a[i] >> a[i];
  if (n == 1) return cout << a[0] << '\n', void();

  d[0] = a[0], d[1] = max(a[0], a[1]);
  for (int i = 2; i < n; i++) d[i] = max(d[i - 1], d[i - 2] + a[i]);

  cout << d[n - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
