#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAX = 100, INF = 1e9 + 7;
int party[MAX + 1], cost[MAX + 1][MAX + 1];
int n, m;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  for (int i = 1; i <= n; i++) cin >> party[i];
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) cost[i][j] = INF;
    cost[i][i] = 0;
  }

  while (m--) {
    int a, b;
    cin >> a >> b;
    int dist = party[a] != party[b];
    cost[a][b] = cost[b][a] = dist;
  }

  // Floyd-warshall
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) cost[i][j] = min(cost[i][k] + cost[k][j], cost[i][j]);
    }
  }

  int ans = INF;
  for (int i = 1; i <= n; i++) {
    int cur = 0;
    for (int j = 1; j <= n; j++) cur = max(cur, cost[i][j]);
    ans = min(ans, cur);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> n >> m;
    if (n == 0 && m == 0) break;
    solve();
  }
}
