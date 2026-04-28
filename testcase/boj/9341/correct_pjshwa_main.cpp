#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 9;
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
  int A, B, C, D;
  cin >> A >> B >> C >> D;
  C += 2;

  matrix ans = matrix(C, vector<ll>(C));
  matrix a = matrix(C, vector<ll>(C));

  for (int i = 0; i < C; i++) ans[i][i] = 1;
  a[0][1] = 1;
  for (int i = 1; i < C; i++) {
    for (int j = 0; j <= i; j++) a[i][j] = 1;
  }

  // Exponentiation by squaring
  D--;
  while (D) {
    if (D & 1) ans = ans * a;
    a = a * a;
    D /= 2;
  }

  vector<int> v(C, A);
  v[0] = (B - A + MOD) % MOD;

  ll res = 0;
  for (int i = 0; i < C; i++) {
    res = (res + (ll)ans[C - 1][i] * v[i]) % MOD;
  }
  cout << res << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
