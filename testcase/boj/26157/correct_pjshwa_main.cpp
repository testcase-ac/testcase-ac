#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void compress(vector<int>& a) {
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
}

class SCC {
  int n, scc_cnt, dfs_cnt;
  vector<vector<int>> adj;
  vector<int> dfs_order;
  stack<int> S;

  vector<vector<int>> scc_graph;
  vector<int> scc_vis, scc_indegree;

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
    scc_vis.resize(scc_cnt + 1, 0);
    scc_indegree.resize(scc_cnt + 1, 0);

    for (int i = 1; i <= n; i++) {
      for (int j : adj[i]) {
        if (scc[i] == scc[j]) continue;
        scc_graph[scc[i]].push_back(scc[j]);
      }
    }

    for (int i = 1; i <= scc_cnt; i++) {
      compress(scc_graph[i]);
      for (int v : scc_graph[i]) scc_indegree[v]++;
    }
  }

public:
  vector<int> scc;

  SCC(int n) :
    n(n), scc_cnt(0), dfs_cnt(0),
    adj(n + 1), scc(n + 1), dfs_order(n + 1) {
  }

  void add_edge(int a, int b) { adj[a].push_back(b); }

  void perform() {
    for (int i = 1; i <= n; i++) if (!dfs_order[i]) dfs(i);
    reconstruct();
  }

  void debug() {
    for (int i = 1; i <= n; i++) {
      cout << "scc[" << i << "] = " << scc[i] << '\n';
    }
    for (int i = 1; i <= scc_cnt; i++) {
      cout << "scc_graph[" << i << "] = ";

      if (scc_graph[i].empty()) cout << "empty\n";
      else {
        for (int v : scc_graph[i]) cout << v << ' ';
        cout << '\n';
      }
    }
  }

  // If DAG is linear, return its source.
  // Otherwise, return -1.
  int linear_dag_source() {
    queue<int> q;
    vector<int> indegree(scc_indegree);

    int o = -1;
    for (int i = 1; i <= scc_cnt; i++) {
      if (indegree[i] == 0) {
        q.push(i);
        o = i;
      }
    }

    while (!q.empty()) {
      if (q.size() > 1) return -1;

      int cur = q.front(); q.pop();
      for (int nxt : scc_graph[cur]) {
        if (--indegree[nxt] == 0) q.push(nxt);
      }
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
    c.add_edge(u, v);
  }
  c.perform();

  // c.debug();

  int o = c.linear_dag_source();
  vector<int> ans;
  for (int i = 1; i <= N; i++) {
    if (c.scc[i] == o) ans.push_back(i);
  }

  if (ans.empty()) cout << "0\n";
  else {
    cout << ans.size() << '\n';
    for (int e : ans) cout << e << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
