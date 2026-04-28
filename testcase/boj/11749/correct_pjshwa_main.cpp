#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

matrix operator * (const matrix &a, const matrix &b) {
  int n = a.size();
  matrix c(n, vector<ll>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) c[i][j] |= (a[i][k] & b[k][j]);
    }
  }
  return c;
}

const int MAX = 50, INF = 1e9 + 7;
int reach[MAX + 1];

void solve() {
  int n, m, a, b, c;
  cin >> n >> m >> a >> b >> c;

  matrix x = matrix(n, vector<ll>(n));
  matrix w = x, wa = x, wb = x, wc = x;
  for (int i = 0; i < n; i++) x[i][i] = 1;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    w[u - 1][v - 1] = 1;
  }

  for (int it = 1; it <= 100; it++) {
    x = x * w;
    if (it == a) wa = x;
    if (it == b) wb = x;
    if (it == c) wc = x;
  }

  fill(reach, reach + n + 1, INF);
  reach[n] = 0;

  for (int i = 1; i <= n; i++) {

  }

  bool changed = 1;
  while (changed) {
    changed = false;
    for (int i = 1; i <= n; i++) {
      int cv = 0, cur;

      cur = INF;
      for (int j = 1; j <= n; j++) if (wa[i - 1][j - 1]) cur = min(cur, reach[j]);
      cv = max(cv, cur + 1);

      cur = INF;
      for (int j = 1; j <= n; j++) if (wb[i - 1][j - 1]) cur = min(cur, reach[j]);
      cv = max(cv, cur + 1);

      cur = INF;
      for (int j = 1; j <= n; j++) if (wc[i - 1][j - 1]) cur = min(cur, reach[j]);
      cv = max(cv, cur + 1);

      if (reach[i] > cv) {
        changed = true;
        reach[i] = cv;
      }
    }
  }

  if (reach[1] == INF) cout << "IMPOSSIBLE\n";
  else cout << reach[1] << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
