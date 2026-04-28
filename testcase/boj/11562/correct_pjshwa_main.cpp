#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int cost[251][251];
const int MAX = 1e9 + 7;

int main() {
  fast_io();

  int n, m, u, v, b;
  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i == j) cost[i][j] = 0;
      else cost[i][j] = MAX;
    }
  }

  while (m--) {
    cin >> u >> v >> b;
    cost[u][v] = 0;
    cost[v][u] = 1;
    if (b) cost[v][u] = 0;
  }

  // Floyd-warshall
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) cost[i][j] = min(cost[i][k] + cost[k][j], cost[i][j]);
    }
  }

  cin >> m;
  while (m--) {
    cin >> u >> v;
    cout << cost[u][v] << '\n';
  }
}
