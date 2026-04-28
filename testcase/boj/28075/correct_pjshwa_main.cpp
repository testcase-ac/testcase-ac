#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
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
  ll K; int M; cin >> K >> M;

  vector<vector<int>> B(2, vector<int>(3));
  for (int i = 0; i < 2; ++i) for (int j = 0; j < 3; ++j) cin >> B[i][j];

  int L = 25, N = 6 * (L + 1);
  matrix A = matrix(N, vector<ll>(N, 0));
  matrix U = matrix(N, vector<ll>(N, 0));
  for (int i = 0; i < N; ++i) U[i][i] = 1;
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    int v_i = i / 6, v_j = j / 6;
    int type_j = (j - v_j * 6) / 3;
    int pos_i = (i - v_i * 6) % 3, pos_j = (j - v_j * 6) % 3;

    int add = B[type_j][pos_j];
    if (pos_i == pos_j) add /= 2;

    if (min(L, v_i + add) == v_j) A[i][j] = 1;
  }

  K--;
  while (K) {
    if (K & 1) U = U * A;
    A = A * A;
    K >>= 1;
  }

  int ans = 0;
  for (int type = 0; type < 2; ++type) for (int pos = 0; pos < 3; ++pos) {
    int i = 6 * B[type][pos] + 3 * type + pos;
    for (int j = 0; j < N; ++j) {
      int v_j = j / 6;
      if (v_j >= M) ans = (ans + U[i][j]) % MOD;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
