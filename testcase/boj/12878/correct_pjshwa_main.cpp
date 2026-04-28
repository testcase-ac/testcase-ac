#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 10007;
matrix operator * (const matrix &a, const matrix &b) {
  int n = a.size();
  matrix c(n, vector<ll>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
    }
  }
  return c;
}

void solve() {
  int k;
  cin >> k;

  matrix ans = matrix(4, vector<ll>(4));
  matrix a = matrix(4, vector<ll>(4));
  a[0][0] = a[1][1] = a[2][2] = a[3][3] = 2;
  a[0][1] = a[0][2] = a[1][0] = a[1][3] = a[2][0] = a[2][3] = a[3][1] = a[3][2] = 1;
  for (int i = 0; i < 4; i++) ans[i][i] = 1;

  while (k) {
    if (k & 1) ans = ans * a;
    a = a * a;
    k >>= 1;
  }

  cout << ans[0][0] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
