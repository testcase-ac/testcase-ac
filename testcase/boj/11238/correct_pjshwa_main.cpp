#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7;
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
  ll n, m;
  cin >> n >> m;

  n = __gcd(n, m);
  matrix ans = matrix(2, vector<ll>(2));
  matrix a = matrix(2, vector<ll>(2));

  for (int i = 0; i < 2; i++) ans[i][i] = 1;
  a[0][0] = a[0][1] = a[1][0] = 1;

  // Exponentiation by squaring
  while (n) {
    if (n & 1) ans = ans * a;
    a = a * a;
    n /= 2;
  }
  cout << ans[1][0] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
