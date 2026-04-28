#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 400, INF = 0x3f3f3f3f;
int cost[MAX + 1][MAX + 1];

void solve() {
  int N, M; cin >> N >> M;
  
  memset(cost, 0x3f, sizeof(cost));
  for (int i = 1; i <= N; i++) cost[i][i] = 0;

  while (M--) {
    int u, v, w; cin >> u >> v >> w;
    cost[u][v] = min(cost[u][v], w);
  }

  for (int k = 1; k <= N; k++) for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) {
    cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
  }

  int ans = INF;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) {
    if (i == j || cost[i][j] == INF || cost[j][i] == INF) continue;
    ans = min(ans, cost[i][j] + cost[j][i]);
  }

  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
