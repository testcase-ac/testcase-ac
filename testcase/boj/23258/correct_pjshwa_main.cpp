#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 300, INF = 1e9 + 7;
int cost[MAX + 1][MAX + 1][MAX + 1];

int main() {
  fast_io();

  int n, q;
  cin >> n >> q;

  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
    cin >> cost[0][i][j];
    if (cost[0][i][j] == 0) cost[0][i][j] = INF;
    if (i == j) cost[0][i][j] = 0;
  }

  // Floyd-warshall
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        cost[k][i][j] = min(cost[k - 1][i][k] + cost[k - 1][k][j], cost[k - 1][i][j]);
      }
    }
  }

  while (q--) {
    int c, s, e;
    cin >> c >> s >> e;
    if (cost[c - 1][s][e] == INF) cout << -1 << '\n';
    else cout << cost[c - 1][s][e] << '\n';
  }
}
