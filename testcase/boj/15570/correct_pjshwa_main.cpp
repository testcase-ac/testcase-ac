#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e2, MOD = 1999;
int dp1[MAXN + 1], dp2[MAXN + 1];

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
  int N; ll M; cin >> N >> M;

  dp1[0] = 1;
  for (int i = 1; i <= N; ++i) for (int j = 1; j <= i; ++j) {
    dp1[i] = (dp1[i] + dp1[i - j]) % MOD;
  }

  matrix ans = matrix(N, vector<ll>(N));
  for (int i = 0; i < N; ++i) ans[i][i] = 1;

  matrix a = matrix(N, vector<ll>(N));
  for (int i = 1; i < N; ++i) a[i - 1][i] = a[N - 1][i] = 1;
  a[N - 1][0] = dp1[N];

  // Exponentiation by squaring
  while (M) {
    if (M & 1) ans = ans * a;
    a = a * a;
    M /= 2;
  }

  int res = 0;
  for (int j = 0; j < N; ++j) res = (res + ans[0][j] * dp1[j]) % MOD;
  cout << res << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
