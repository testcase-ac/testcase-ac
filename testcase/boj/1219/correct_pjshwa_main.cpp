#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
const ll INF = 1e18;
ll cdist[MAX + 1];
int g[MAX + 1];
vector<pii> graph[MAX + 1];
vector<int> rgraph[MAX + 1];
bool vis[MAX + 1];

void dfs(int v) {
  vis[v] = 1;
  for (int d : rgraph[v]) {
    if (!vis[d]) dfs(d);
  }
}

void solve() {
  int n, s, e, m;
  cin >> n >> s >> e >> m;
  vector<tii> edges;
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    edges.emplace_back(u, v, w);
  }
  for (int i = 0; i < n; i++) cin >> g[i];
  for (auto& [u, v, w] : edges) {
    graph[u].emplace_back(v, w - g[v]);
    rgraph[v].emplace_back(u);
  }

  // Bellman-ford
  for (int i = 0; i < n; i++) cdist[i] = INF;
  cdist[s] = -g[s];

  // Check reachability from e
  dfs(e);

  bool neg_cycle = false;
  for (int it = 1; it <= n; it++) {
    for (int i = 0; i < n; i++) {
      for (auto& [v, w] : graph[i]) {
        if (cdist[i] != INF && cdist[v] > cdist[i] + w) {
          cdist[v] = cdist[i] + w;
          if (vis[v] && it == n) neg_cycle = true;
        }
      }
    }
  }

  if (cdist[e] == INF) cout << "gg\n";
  else if (neg_cycle) cout << "Gee\n";
  else cout << -cdist[e] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
