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

  vector<vector<int>> scc_graph;

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
  vector<int> scc_vis, scc_indegree;
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
};

void solve() {
  int N, M; cin >> N >> M;

  SCC c(N);
  while (M--) {
    int u, v; cin >> u >> v;
    c.add_edge(u, v);
  }
  c.perform();

  set<int> need;
  for (int i = 1; i <= c.scc_cnt; i++) {
    if (c.scc_indegree[i] == 0) need.insert(i);
  }

  int T, ans = 0; cin >> T;
  while (T--) {
    int x; cin >> x;
    if (need.count(c.scc[x])) {
      ans++;
      need.erase(c.scc[x]);
    }
  }

  if (need.size()) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
