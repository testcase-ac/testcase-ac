#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int cost[100][100];
int idg[100], odg[100];
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

  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (cost[i][j] < MAX) {
        odg[i]++;
        idg[j]++;
      }
      if (cost[j][i] < MAX) {
        idg[i]++;
        odg[j]++;
      }
    }
  }

  int h = (n + 1) / 2;
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (idg[i] >= h || odg[i] > n - h) ans++;
  }
  cout << ans;

}
