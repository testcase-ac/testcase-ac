#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX], b[MAX];

// Binomial Coefficient mod 2
int C(int n, int k) {
  return (n & k) == k;
}

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int j = 0; j < m; j++) cin >> b[j];

  int nadd = 0, madd = 0;
  for (int i = 0; i < n; i++) nadd = (nadd + a[i] * C(n - 1 - i + m - 1, n - 1 - i)) % 2;
  for (int j = 0; j < m; j++) madd = (madd + b[j] * C(n - 1 + m - 1 - j, m - 1 - j)) % 2;
  cout << (nadd + madd) % 2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
