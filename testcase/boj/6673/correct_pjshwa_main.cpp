#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 10000;
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

int N;
void solve() {
  matrix ans = matrix(N, vector<ll>(N));
  for (int i = 0; i < N; ++i) ans[i][i] = 1;

  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];

  matrix a = matrix(N, vector<ll>(N));
  for (int i = 1; i < N; ++i) a[i][i - 1] = 1;
  for (int j = 0; j < N; ++j) cin >> a[0][j];

  int i; cin >> i;
  if (i < N) return cout << A[i] << '\n', void();

  int K = i - N + 1;
  while (K) {
    if (K & 1) ans = ans * a;
    a = a * a;
    K /= 2;
  }

  ll res = 0;
  for (int j = 0; j < N; ++j) res = (res + ans[0][j] * A[N - 1 - j]) % MOD;
  cout << res << '\n';
}

int main() {
  fast_io();

  while (cin >> N) {
    if (N == 0) break;
    solve();
  }
}
