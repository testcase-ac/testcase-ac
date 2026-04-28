#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e8 + 7;
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
  int k, n;
  cin >> k >> n;

  matrix ans = matrix(k + 1, vector<ll>(k + 1));
  matrix a = matrix(k + 1, vector<ll>(k + 1));

  ans[0][0] = 1;
  for (int i = 1; i <= k; i++) {
    ans[i][i] = a[i][i - 1] = 1;
  }
  a[0][0]++; a[0][k]++;

  // Exponentiation by squaring
  while (n) {
    if (n & 1) ans = ans * a;
    a = a * a;
    n /= 2;
  }

  int res = 0;
  for (int j = 0; j <= k; j++) res = (res + ans[k][j]) % MOD;
  cout << res << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
