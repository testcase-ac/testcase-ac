#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int cost[401][401];
const int MAX = 1e9 + 7;

int main() {
  fast_io();

  int n, m, a, b;
  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i != j) cost[i][j] = MAX;
    }
  }

  while (m--) {
    cin >> a >> b;
    cost[a][b] = 1;
  }

  // Floyd-warshall
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) cost[i][j] = min(cost[i][k] + cost[k][j], cost[i][j]);
    }
  }

  cin >> m;
  while (m--) {
    cin >> a >> b;
    if (cost[a][b] < MAX) cout << -1;
    else if (cost[b][a] < MAX) cout << 1;
    else cout << 0;
    cout << '\n';
  }
}
