#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
vector<pii> graph[MAX + 1];
int cdist[3][MAX + 1];
int from[3][MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;
  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].emplace_back(v, w);
    graph[v].emplace_back(u, w);
  }

  int a[3];
  cin >> a[0] >> a[1] >> a[2];

  memset(from, -1, sizeof(from));

  queue<pii> q;
  for (int i = 0; i < 3; i++) {
    fill(cdist[i], cdist[i] + MAX + 1, INF);
    cdist[i][a[i]] = 0;

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, a[i]});

    while (!pq.empty()) {
      auto [wi, ui] = pq.top();
      pq.pop();

      if (wi > cdist[i][ui]) continue;

      for (auto& [vi, di] : graph[ui]) {
        if (cdist[i][vi] > di + wi) {
          cdist[i][vi] = di + wi;
          from[i][vi] = ui;
          pq.push({cdist[i][vi], vi});
        }
      }
    }
  }

  int mdist = INF;
  for (int u = 1; u <= n; u++) {
    if (cdist[0][u] == INF || cdist[1][u] == INF || cdist[2][u] == INF) continue;
    mdist = min(mdist, cdist[0][u] + cdist[1][u] + cdist[2][u]);
  }

  for (int u = 1; u <= n; u++) {
    if (cdist[0][u] == INF || cdist[1][u] == INF || cdist[2][u] == INF) continue;
    if (cdist[0][u] + cdist[1][u] + cdist[2][u] != mdist) continue;

    vector<pii> edges;
    for (int i = 0; i < 3; i++) {
      int v = u;
      while (from[i][v] != -1) {
        edges.push_back({from[i][v], v});
        v = from[i][v];
      }
    }
    cout << mdist << ' ' << edges.size() << '\n';
    for (auto& [u, v] : edges) {
      cout << u << ' ' << v << '\n';
    }
    return;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
