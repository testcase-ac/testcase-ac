#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, a[4]; cin >> n >> a[0] >> a[1] >> a[2] >> a[3];
  for (int i = 1; i <= n - 1; i++) {
    cout << i << ' ';
    if (i == a[0] || i == a[1]) cout << "1\n";
    else if (i == a[2] || i == a[3]) cout << "-1\n";
    else cout << "0\n";
  }

  cout << n << ' '; int L = 1e9;
  if (n == a[0] || n == a[1]) cout << L << '\n';
  else cout << -L << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
