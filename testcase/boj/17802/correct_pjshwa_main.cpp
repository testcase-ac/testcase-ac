#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, x;
  cin >> n >> x;

  if (x < (1 << (n - 1))) return cout << "impossible\n", void();

  int a[n][n];
  for (int i = 0; i < n - 1; i++) a[0][i] = 1;
  a[0][n - 1] = x + 1 - (1 << (n - 1));

  for (int i = 1; i < n; i++) for (int j = 0; j < n - i; j++) {
    a[i][j] = a[i - 1][j] + a[i - 1][j + 1];
  }

  for (int i = n - 1; i >= 0; i--) {
    for (int j = 0; j < n - i; j++) cout << a[i][j] << " ";
    cout << "\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
