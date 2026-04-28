#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, INF = 0x3f3f3f3f;
int parent[MAXN + 1];
int cost[MAXN + 1][MAXN + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

void solve() {
  int N, M; cin >> N >> M;

  for (int i = 1; i <= N; ++i) {
    parent[i] = i;
    for (int j = i + 1; j <= N; ++j) {
      cost[i][j] = cost[j][i] = INF;
    }
  }

  while (M--) {
    int u, v; cin >> u >> v;
    cost[u][v] = cost[v][u] = 1;
    Union(u, v);
  }

  // Floyd-Warshall
  for (int k = 1; k <= N; ++k) for (int u = 1; u <= N; ++u) for (int v = 1; v <= N; ++v) {
    if (cost[u][v] > cost[u][k] + cost[k][v]) cost[u][v] = cost[u][k] + cost[k][v];
  }

  vector<vector<int>> groups(N + 1);
  for (int i = 1; i <= N; ++i) groups[Find(i)].push_back(i);

  vector<int> ans;
  for (int g = 1; g <= N; ++g) {
    if (groups[g].empty()) continue;

    int repu, maxd = INF;
    for (int u : groups[g]) {
      int curd = 0;
      for (int v : groups[g]) {
        if (u == v) continue;
        curd = max(curd, cost[u][v]);
      }
      if (curd < maxd) {
        repu = u;
        maxd = curd;
      }
    }
    ans.push_back(repu);
  }

  sort(ans.begin(), ans.end());
  cout << ans.size() << '\n';
  for (int u : ans) cout << u << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
