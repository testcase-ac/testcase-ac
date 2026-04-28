#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
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
      for (int k = 0; k < n; k++) c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % (MOD - 1);
    }
  }
  return c;
}

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

void solve() {
  ll n, f[3], c; cin >> n >> f[0] >> f[1] >> f[2] >> c;

  matrix A = matrix(5, vector<ll>(5, 0));
  matrix L = matrix(5, vector<ll>(5, 0));
  for (int i = 0; i < 5; ++i) L[i][i] = 1;
  // [[0 1 0 0 0]]
  // [[0 0 1 0 0]]
  // [[1 1 1 1 0]]
  // [[0 0 0 1 2]]
  // [[0 0 0 0 1]]
  A[2][0] = A[2][1] = A[2][2] = A[2][3] = 1;
  A[0][1] = A[1][2] = A[3][3] = A[4][4] = 1;
  A[3][4] = 2;

  ll E = n - 3;
  while (E) {
    if (E & 1) L = L * A;
    A = A * A;
    E /= 2;
  }

  ll ans = 1;
  for (int i = 0; i < 3; ++i) ans = (ans * lpow(f[i], L[2][i], MOD)) % MOD;

  ll ce = 2 * L[2][3] + L[2][4];
  ans = (ans * lpow(c, ce, MOD)) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
