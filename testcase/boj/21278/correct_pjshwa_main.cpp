#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int cost[101][101];
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
    cost[b][a] = 1;
  }

  // Floyd-warshall
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) cost[i][j] = min(cost[i][k] + cost[k][j], cost[i][j]);
    }
  }

  int mi1, mi2, msum, mv = 1e9; 
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      msum = 0;
      for (int k = 1; k <= n; k++) msum += min(cost[i][k], cost[j][k]);

      if (msum < mv) {
        mi1 = i;
        mi2 = j;
        mv = msum;
      }
    }
  }

  cout << mi1 << ' ' << mi2 << ' ' << mv * 2 << '\n';
}
