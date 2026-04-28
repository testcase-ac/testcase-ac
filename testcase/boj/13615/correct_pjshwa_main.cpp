#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e4;

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
  int N, L, S, T; cin >> N >> L >> S >> T; --S; --T;

  matrix ans = matrix(N, vector<ll>(N));
  matrix a = matrix(N, vector<ll>(N));

  for (int i = 0; i < N; ++i) ans[i][i] = 1;
  for (int i = 0; i < N; i++) for (int j = 0; j < 4; ++j) {
    int x; cin >> x;
    a[i][x - 1] += 1;
  }

  // Exponentiation by squaring
  while (L) {
    if (L & 1) ans = ans * a;
    a = a * a;
    L /= 2;
  }

  cout << ans[S][T] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
