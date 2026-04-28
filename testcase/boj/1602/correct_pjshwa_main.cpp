#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 500, INF = 0x3f3f3f3f;
int A[MAX + 1], cost[MAX + 1][MAX + 1], cost_ww[MAX + 1][MAX + 1];

void solve() {
  int N, M, Q; cin >> N >> M >> Q;

  memset(cost, 0x3f, sizeof(cost));
  memset(cost_ww, 0x3f, sizeof(cost_ww));
  for (int i = 1; i <= N; ++i) {
    cin >> A[i];
    cost[i][i] = 0;
  }

  while (M--) {
    int u, v, w; cin >> u >> v >> w;

    cost[u][v] = min(cost[u][v], w);
    cost[v][u] = min(cost[v][u], w);

    int p = max(A[u], A[v]);
    cost_ww[u][v] = min(cost_ww[u][v], p + w);
    cost_ww[v][u] = min(cost_ww[v][u], p + w);
  }

  vector<pii> by_w;
  for (int i = 1; i <= N; ++i) by_w.emplace_back(A[i], i);
  sort(by_w.begin(), by_w.end());

  // Floyd-Warshall
  for (auto [_, k] : by_w) {
    for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) {
      cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
      cost_ww[i][j] = min(cost_ww[i][j], cost[i][j] + max({A[i], A[j], A[k]}));
    }
  }

  while (Q--) {
    int u, v; cin >> u >> v;
    cout << (cost_ww[u][v] == INF ? -1 : cost_ww[u][v]) << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
