#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 256, INF = 1e9 + 7;
int cost[MAX + 1][MAX + 1];

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) {
    if (i != j) cost[i][j] = INF;
  }

  while (M--) {
    int u, v;
    cin >> u >> v;
    cost[u][v] = 1;
  }

  // Floyd-Warshall
  for (int k = 1; k <= N; k++) {
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
      }
    }
  }

  vector<pii> ans(N + 1);
  for (int i = 1; i <= N; i++) {
    int f = 0, b = 0;
    for (int j = 1; j <= N; j++) {
      if (i == j) continue;
      if (cost[i][j] == INF && cost[j][i] != INF) f++;
      if (cost[i][j] != INF && cost[j][i] == INF) b++;
      if (cost[i][j] != INF && cost[j][i] != INF) {
        cout << "-1\n";
        return;
      }
    }
    ans[i] = {f + 1, N - b};
  }

  for (int i = 1; i <= N; i++) {
    cout << ans[i].first << " " << ans[i].second << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
