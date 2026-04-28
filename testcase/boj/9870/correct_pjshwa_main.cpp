#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 400, INF = 1e9 + 7, BIAS = 200;
int cost[MAX + 1][MAX + 1];

int main() {
  fast_io();

  int n, m, k, q;
  cin >> n >> m >> k >> q;

  for (int i = 1; i <= MAX; i++) {
    for (int j = 1; j <= MAX; j++) {
      if (i != j) cost[i][j] = INF;
    }
  }
  for (int i = 1; i <= k; i++) cost[i][i + BIAS] = 0;

  while (m--) {
    int a, b, c;
    cin >> a >> b >> c;
    cost[a][b] = c;
    cost[a + BIAS][b + BIAS] = c;
  }

  // Floyd-warshall
  for (int k = 1; k <= MAX; k++) {
    for (int i = 1; i <= MAX; i++) {
      for (int j = 1; j <= MAX; j++) cost[i][j] = min(cost[i][k] + cost[k][j], cost[i][j]);
    }
  }

  ll ans = 0, cnt = 0;
  while (q--) {
    int u, v;
    cin >> u >> v;
    if (cost[u][v + BIAS] < INF) {
      ans += cost[u][v + BIAS];
      cnt++;
    }
  }

  cout << cnt << '\n' << ans << '\n';
}
