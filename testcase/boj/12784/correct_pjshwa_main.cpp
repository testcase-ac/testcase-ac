#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAXN = 1000, INF = 1e9 + 7;
vector<pii> graph[MAXN + 1];
int indegree[MAXN + 1], d[MAXN + 1];

// Cost for node v to ban all connections from leaves
int r(int v, int p) {
  if (d[v] != -1) return d[v];
  if (v != 1 && indegree[v] == 1) return d[v] = INF;

  int res = 0;
  for (auto& [u, w] : graph[v]) {
    if (u == p) continue;
    res += min(r(u, v), w);
  }

  return d[v] = res;
}

void solve() {
  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= n; i++) graph[i].clear();
  memset(d, -1, sizeof(d));
  memset(indegree, 0, sizeof(indegree));

  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].emplace_back(v, w);
    graph[v].emplace_back(u, w);
    indegree[u]++;
    indegree[v]++;
  }

  cout << r(1, -1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
