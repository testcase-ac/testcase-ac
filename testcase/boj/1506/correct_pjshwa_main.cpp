#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

struct SCC {
  int n, scc_cnt, dfs_cnt;
  vector<vector<int>> adj;
  vector<int> scc, dfs_order;
  stack<int> S;

  vector<vector<int>> scc_graph;
  vector<int> scc_vis, scc_indegree;

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

  void reconstruct() {
    scc_graph.resize(scc_cnt + 1);
    scc_vis.resize(scc_cnt + 1, 0);
    scc_indegree.resize(scc_cnt + 1, 0);

    for (int i = 1; i <= n; i++) {
      for (int j : adj[i]) {
        if (scc[i] != scc[j]) {
          scc_graph[scc[i]].push_back(scc[j]);
          scc_indegree[scc[j]]++;
        }
      }
    }
  }

  void perform() {
    for (int i = 1; i <= n; i++) if (!dfs_order[i]) dfs(i);
    reconstruct();
  }
};

void solve() {
  int N;
  cin >> N;

  vector<int> cost(N + 1);
  for (int i = 1; i <= N; i++) cin >> cost[i];

  SCC c(N);
  for (int i = 1; i <= N; i++) {
    string S;
    cin >> S;
    for (int j = 0; j < N; j++) {
      if (S[j] == '1') c.add_edge(i, j + 1);
    }
  }
  c.perform();

  map<int, int> scc_cost;
  for (int i = 1; i <= N; i++) {
    if (scc_cost.count(c.scc[i])) {
      scc_cost[c.scc[i]] = min(scc_cost[c.scc[i]], cost[i]);
    }
    else {
      scc_cost[c.scc[i]] = cost[i];
    }
  }

  int ans = 0;
  for (auto [_, v] : scc_cost) ans += v;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
