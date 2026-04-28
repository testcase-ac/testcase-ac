#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, INF = 0x3f3f3f3f;
int p[MAX + 1], cost[MAX + 1][MAX + 1];

void solve() {
  int n, m; cin >> n >> m;
  if (m == 1) return cout << "0\n", void();

  vector<int> B;
  for (int i = 1; i <= n; i++) {
    cin >> p[i];
    if (p[i] == 1) B.push_back(i);
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) cost[i][j] = INF;
    cost[i][i] = 0;
  }
  for (int i = 1; i <= n - 1; i++) {
    int u, v; cin >> u >> v;
    cost[u][v] = cost[v][u] = 1;
  }

  // Floyd-Warshall
  for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
    cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
  }

  int ans = INF;
  for (int u : B) for (int v : B) {
    if (u == v) continue;

    int mcost = cost[u][v], cnt = 2;
    for (int z : B) {
      if (z == u || z == v) continue;
      if (cost[u][z] <= mcost && cost[z][v] <= mcost) cnt++;
    }
    if (cnt >= m) ans = min(ans, mcost);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
