#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 998244353;

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
  ll K; cin >> K;
  K--;

  matrix a = matrix(5, vector<ll>(5, 0));
  matrix ans = matrix(5, vector<ll>(5, 0));
  for (int i = 0; i < 5; i++) ans[i][i] = 1;

  for (int i = 0; i < 4; i++) a[i][i + 1] = 1;
  a[4][0] = a[4][4] = 1;

  while (K) {
    if (K & 1) ans = ans * a;
    a = a * a;
    K >>= 1;
  }

  ll C[5] = {1, 1, 1, 2, 2}, W = 0;
  for (int i = 0; i < 5; i++) W = (W + C[i] * ans[0][i]) % MOD;
  cout << W << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
