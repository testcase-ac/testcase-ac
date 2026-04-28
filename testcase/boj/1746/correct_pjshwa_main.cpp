#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;

matrix operator * (const matrix &a, const matrix &b) {
  int n = a.size();
  matrix c(n, vector<ll>(n, INF));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
    }
  }
  return c;
}

void solve() {
  int k, t, s, e;
  cin >> k >> t >> s >> e;

  int n = 200;
  matrix ans = matrix(n, vector<ll>(n, INF));
  matrix a = matrix(n, vector<ll>(n, INF));

  map<int, int> v2x;
  int idx = 0;
  while (t--) {
    int l, u, v;
    cin >> l >> u >> v;

    if (!v2x.count(u)) v2x[u] = idx++;
    if (!v2x.count(v)) v2x[v] = idx++;

    u = v2x[u], v = v2x[v];
    ans[u][v] = ans[v][u] = a[u][v] = a[v][u] = l;
  }

  // Exponentiation by squaring
  k--;
  while (k) {
    if (k & 1) ans = ans * a;
    a = a * a;
    k /= 2;
  }

  cout << ans[v2x[s]][v2x[e]] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
