#include <bits/stdc++.h>
#define tii tuple<int, int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int cost[201][201];
vector<tii> edges;
const int MAX = 1e9 + 7;

int main() {
  fast_io();

  int n, m, a, b, c;
  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i != j) cost[i][j] = MAX;
    }
  }

  while (m--) {
    cin >> a >> b >> c;
    if (c < cost[a][b]) {
      cost[a][b] = c;
      cost[b][a] = c;
    }
    edges.push_back({a, b, c});
  }

  // Floyd-warshall
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) cost[i][j] = min(cost[i][k] + cost[k][j], cost[i][j]);
    }
  }

  int e1, e2, w, mtv = 1e9, mv;
  for (int i = 1; i <= n; i++) {
    mv = 0;
    for (tii p : edges) {
      tie(e1, e2, w) = p;
      mv = max(mv, cost[i][e1] + cost[i][e2] + w);
    }
    mtv = min(mv, mtv);
  }

  cout << mtv / 2;
  if (mtv & 1) cout << ".5\n";
  else cout << ".0\n";
}
