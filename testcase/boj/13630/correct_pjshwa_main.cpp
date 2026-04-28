#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e6;

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
  ll P, K, L; cin >> P >> K >> L; P /= 5;
  K %= MOD; L %= MOD;

  matrix A = matrix(3, vector<ll>(3, 0));
  matrix ans = matrix(3, vector<ll>(3, 0));
  for (int i = 0; i < 3; ++i) ans[i][i] = 1;
  A[0][0] = K; A[0][1] = L;
  A[1][0] = 1; A[1][1] = 0;
  A[2][1] = 1;

  while (P) {
    if (P & 1) ans = ans * A;
    A = A * A;
    P >>= 1;
  }

  ll B[3] = {(K * K + L) % MOD, K, 1}, ret = 0;
  for (int i = 0; i < 3; ++i) ret = (ret + B[i] * ans[2][i]) % MOD;

  string ret_s = to_string(ret);
  while (ret_s.size() < 6) ret_s = "0" + ret_s;
  cout << ret_s << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
