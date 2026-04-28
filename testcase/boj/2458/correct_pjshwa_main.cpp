#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int cost[501][501];
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

  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    bool able = true;
    for (int j = 1; j <= n; j++) {
      if (cost[i][j] == MAX && cost[j][i] == MAX) able = false;
    }
    if (able) cnt++;
  }

  cout << cnt << '\n';
}
