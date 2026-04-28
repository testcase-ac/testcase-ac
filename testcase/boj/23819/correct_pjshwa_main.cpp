#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int P;
matrix operator * (const matrix &a, const matrix &b) {
  int n = a.size();
  matrix c(n, vector<ll>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % P;
    }
  }
  return c;
}

void solve() {
  int k, n;
  cin >> k >> n;
  vector<ll> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  cin >> P;

  matrix m = matrix(n, vector<ll>(n));
  matrix ans = matrix(n, vector<ll>(n));
  for (int i = 0; i < n; i++) m[0][i] = 1;
  for (int i = 0; i < n; i++) ans[i][i] = 1;
  for (int i = 0; i < n - 1; i++) m[i + 1][i] = 1;

  k -= n;
  // Exponentiation by squaring
  while (k) {
    if (k & 1) ans = ans * m;
    m = m * m;
    k /= 2;
  }

  ll res = 0;
  for (int i = 0; i < n; i++) res = (res + ans[0][i] * v[n - 1 - i]) % P;
  cout << res << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
