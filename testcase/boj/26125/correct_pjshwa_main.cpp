#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 300, INF = 0x3f3f3f3f;
ll cost[MAX + 1][MAX + 1];

void solve() {
  int N, M, S, T;
  cin >> N >> M >> S >> T;

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      if (i != j) cost[i][j] = INF;
    }
  }

  while (M--) {
    ll u, v, w;
    cin >> u >> v >> w;
    cost[u][v] = min(cost[u][v], w);
  }

  // Floyd-warshall
  for (int k = 1; k <= N; k++) {
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) cost[i][j] = min(cost[i][k] + cost[k][j], cost[i][j]);
    }
  }

  int Q;
  cin >> Q;
  while (Q--) {
    int a1, b1, c1, a2, b2, c2;
    cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;

    // S -> T
    ll ans = cost[S][T];

    // S -> 1 -> T
    ans = min(ans, cost[S][a1] + c1 + cost[b1][T]);

    // S -> 1 -> 2 -> T
    ans = min(ans, cost[S][a1] + c1 + cost[b1][a2] + c2 + cost[b2][T]);

    // S -> 2 -> T
    ans = min(ans, cost[S][a2] + c2 + cost[b2][T]);

    // S -> 2 -> 1 -> T
    ans = min(ans, cost[S][a2] + c2 + cost[b2][a1] + c1 + cost[b1][T]);

    if (ans >= INF) ans = -1;
    cout << ans << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
