#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int a[4]; cin >> a[0] >> a[1] >> a[2] >> a[3];
  sort(a, a + 4);
  cout << a[0] * a[1] + a[2] * a[3] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
