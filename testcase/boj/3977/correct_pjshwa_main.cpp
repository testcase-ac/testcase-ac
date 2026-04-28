#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

struct SCC {
  int n, scc_cnt, dfs_cnt;
  vector<vector<int>> adj;
  vector<int> scc, dfs_order;
  stack<int> S;

  SCC(int n) :
    n(n), scc_cnt(0), dfs_cnt(0),
    adj(n + 1), scc(n + 1), dfs_order(n + 1) {
  }

  void add_edge(int a, int b) { adj[a].push_back(b); }

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

  void perform() {
    for (int i = 1; i <= n; i++) if (!dfs_order[i]) dfs(i);
  }

  vector<vector<int>> graph;
  vector<int> vis, indegree;
  void reconstruct() {
    graph.resize(scc_cnt + 1);
    vis.resize(scc_cnt + 1, 0);
    indegree.resize(scc_cnt + 1, 0);

    for (int i = 1; i <= n; i++) {
      for (int j : adj[i]) {
        if (scc[i] != scc[j]) {
          graph[scc[i]].push_back(scc[j]);
          indegree[scc[j]]++;
        }
      }
    }
  }

  // If scc has single source, return it.
  // Otherwise, return -1.
  int is_single_source() {
    int o = -1;
    queue<int> q;
    for (int i = 1; i <= scc_cnt; i++) {
      if (indegree[i] == 0) {
        q.push(i);
        vis[i] = 1;
        o = i;
      }
    }
    if (q.size() != 1) return -1;

    while (!q.empty()) {
      int cur = q.front(); q.pop();
      for (int nxt : graph[cur]) {
        vis[nxt] = 1;
        q.push(nxt);
      }
    }

    for (int i = 1; i <= scc_cnt; i++) {
      if (!vis[i]) return -1;
    }
    return o;
  }
};

void solve() {
  int N, M;
  cin >> N >> M;

  SCC c(N);
  while (M--) {
    int u, v;
    cin >> u >> v;
    c.add_edge(u + 1, v + 1);
  }
  c.perform();
  c.reconstruct();

  int o = c.is_single_source();

  vector<int> ans;
  for (int i = 1; i <= N; i++) {
    if (c.scc[i] == o) ans.push_back(i - 1);
  }

  if (ans.empty()) cout << "Confused\n";
  else for (int e : ans) cout << e << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) {
    solve();
    if (t) cout << '\n';
  }
}
