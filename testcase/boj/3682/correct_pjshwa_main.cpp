#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

struct SCC {
  int n, scc_cnt, dfs_cnt;
  vector<vector<int>> adj;
  vector<int> scc, dfs_order, scc_indegree, scc_outdegree;
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

  void reconstruct() {
    scc_indegree.resize(scc_cnt + 1, 0);
    scc_outdegree.resize(scc_cnt + 1, 0);

    for (int i = 1; i <= n; i++) {
      for (int j : adj[i]) {
        if (scc[i] != scc[j]) {
          scc_indegree[scc[j]]++;
          scc_outdegree[scc[i]]++;
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
  int N, M; cin >> N >> M;

  SCC c(N);
  while (M--) {
    int u, v; cin >> u >> v;
    c.add_edge(u, v);
  }
  c.perform();

  if (c.scc_cnt == 1) cout << "0\n";
  else {
    int cnt_i = 0, cnt_o = 0;
    for (int i = 1; i <= c.scc_cnt; i++) {
      if (c.scc_indegree[i] == 0) cnt_i++;
      if (c.scc_outdegree[i] == 0) cnt_o++;
    }
    cout << max(cnt_i, cnt_o) << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
