#include <bits/stdc++.h>
typedef long long ll;
#define matrix vector<vector<ll>>
using namespace std;

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

int main() {
  fast_io();

  ll n, m;
  cin >> n >> m;

  matrix ans = matrix(m, vector<ll>(m));
  matrix a = matrix(m, vector<ll>(m));
  for (int i = 0; i < m; i++) ans[i][i] = 1;
  a[0][0] = a[0][m - 1] = 1;
  for (int i = 1; i < m; i++) a[i][i - 1] = 1;

  // Exponentiation by squaring
  while (n) {
    if (n & 1) ans = ans * a;
    a = a * a;
    n >>= 1;
  }
  cout << ans[0][0];
}
