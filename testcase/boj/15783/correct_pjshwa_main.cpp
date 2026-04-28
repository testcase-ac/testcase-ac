#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void compress(vector<int>& a) {
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
}

class SCC {
  int n, dfs_cnt;
  vector<vector<int>> adj;
  vector<int> dfs_order;
  stack<int> S;

  int dfs(int cur) {
    int ret = dfs_order[cur] = ++dfs_cnt; S.push(cur);
    for (const auto& nxt : adj[cur]) {
      if (!dfs_order[nxt]) ret = min(ret, dfs(nxt));
      else if (!scc[nxt]) ret = min(ret, dfs_order[nxt]);
    }
    if (ret == dfs_order[cur]) {
      for (scc_cnt++; S.size();) {
        int t = S.top(); S.pop();
        scc[t] = scc_cnt;
        if (t == cur) break;
      }
    }
    return ret;
  }

  void reconstruct() {
    scc_graph.resize(scc_cnt + 1);
    vis.resize(scc_cnt + 1, 0);
    indegree.resize(scc_cnt + 1, 0);

    for (int i = 1; i <= n; i++) {
      for (int j : adj[i]) {
        if (scc[i] == scc[j]) continue;
        scc_graph[scc[i]].push_back(scc[j]);
      }
    }

    for (int i = 1; i <= scc_cnt; i++) {
      compress(scc_graph[i]);
      for (int v : scc_graph[i]) indegree[v]++;
    }
  }

public:
  vector<int> scc, vis, indegree;
  vector<vector<int>> scc_graph;
  int scc_cnt;

  SCC(int n) :
    n(n), scc_cnt(0), dfs_cnt(0),
    adj(n + 1), scc(n + 1), dfs_order(n + 1) {
  }

  void add_edge(int a, int b) { adj[a].push_back(b); }

  void perform() {
    for (int i = 1; i <= n; i++) if (!dfs_order[i]) dfs(i);
    reconstruct();
  }

  void re_dfs(int v) {
    vis[v] = 1;
    for (int u : scc_graph[v]) {
      if (!vis[u]) re_dfs(u);
    }
  }
};

void solve() {
  int N, M; cin >> N >> M;

  SCC c(N);
  while (M--) {
    int u, v; cin >> u >> v;
    c.add_edge(u + 1, v + 1);
  }
  c.perform();

  int ans = 0;
  for (int u = 1; u <= c.scc_cnt; ++u) {
    if (c.indegree[u] == 0) c.re_dfs(u), ++ans;
  }

  // check for cycles
  for (int u = 1; u <= c.scc_cnt; ++u) {
    if (c.vis[u]) continue;
    c.re_dfs(u); ++ans;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
