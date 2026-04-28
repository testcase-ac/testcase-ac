#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int cost[101][101], val[101];
const int INF = 1e9 + 7;

int main() {
  fast_io();

  int n, c, m;
  cin >> n >> c >> m;
  for (int i = 1; i <= n; ++i) cin >> val[i];

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i != j) cost[i][j] = cost[j][i] = INF;
    }
  }

  while (m--) {
    int a, b, l;
    cin >> a >> b >> l;
    if (l < cost[a][b]) cost[a][b] = cost[b][a] = l;
  }

  // Floyd-warshall
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) cost[i][j] = min(cost[i][k] + cost[k][j], cost[i][j]);
    }
  }

  int mval = 0;
  for (int i = 1; i <= n; i++) {
    int cval = 0;
    for (int j = 1; j <= n; j++) {
      if (cost[i][j] <= c) cval += val[j];
    }
    mval = max(mval, cval);
  }

  cout << mval;
}
