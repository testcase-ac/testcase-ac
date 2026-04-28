#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
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
  int N, M, T; cin >> N >> M >> T;

  matrix A = matrix(2 * N, vector<ll>(2 * N, 0));
  matrix ans = matrix(2 * N, vector<ll>(2 * N, 0));
  
  for (int i = 0; i < 2 * N; i++) ans[i][i] = 1;
  for (int i = 0; i < N; ++i) A[i + N][i] = 1;
  while (M--) {
    int op; cin >> op;
    if (op == 1) {
      int a, b; cin >> a >> b; --a; --b;
      A[a][b] += 1;
      A[b][a] += 1;
    }
    if (op == 2) {
      int a, b, c; cin >> a >> b >> c; --a; --b; --c;
      A[a][b + N] += 1; A[a][c + N] += 1;
      A[b][a + N] += 1; A[b][c + N] += 1;
      A[c][a + N] += 1; A[c][b + N] += 1;
    }
  }

  while (T) {
    if (T & 1) ans = ans * A;
    A = A * A;
    T >>= 1;
  }

  for (int i = 0; i < N; ++i) cout << ans[i][0] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
