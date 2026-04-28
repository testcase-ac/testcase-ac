#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 9973;

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
  ll N, M, T; cin >> N >> M >> T;
  matrix ans = matrix(N * N, vector<ll>(N * N));
  for (int i = 0; i < N * N; ++i) ans[i][i] = 1;

  vector<pii> edges;
  while (M--) {
    int u, v; cin >> u >> v;
    edges.emplace_back(u - 1, v - 1);
    edges.emplace_back(v - 1, u - 1);
  }

  matrix a = matrix(N * N, vector<ll>(N * N));
  for (auto& [u1, v1] : edges) for (auto& [u2, v2] : edges) {
    int u = u1 * N + u2, v = v1 * N + v2;
    if (v1 != v2) ++a[u][v];
  }

  --T;
  while (T) {
    if (T & 1) ans = ans * a;
    a = a * a;
    T >>= 1;
  }

  int S = N - 1, ansi = 0;
  for (auto& [u1, v1] : edges) for (auto& [u2, v2] : edges) {
    if (v1 == v2) ansi = (ansi + ans[S][u1 * N + u2]) % MOD;
  }
  cout << ansi << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
