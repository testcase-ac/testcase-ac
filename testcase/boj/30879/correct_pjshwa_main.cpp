#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXT = 2e5, BIAS = 1e5;
const int MAXV = 1e5;

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
};

int V(int x) {
  if (x < 0) return -x + BIAS;
  else return x;
}

void solve() {
  int M; cin >> M;

  vector<tuple<int, int, int>> ops;
  for (int i = 0; i < M; i++) {
    int op; cin >> op;
    if (op == 1) {
      int a, b; cin >> a >> b;
      ops.push_back({op, a, b});
    }
    else ops.push_back({op, 0, 0});
  }

  int l = 0, r = M;
  while (l < r) {
    int m = (l + r) / 2;

    SCC c(MAXT);
    for (int i = 0; i <= m; i++) {
      auto [op, u, v] = ops[i];
      if (op == 2) continue;

      c.add_edge(V(-u), V(v));
      c.add_edge(V(-v), V(u));
    }
    c.perform();

    bool ok = true;
    for (int i = 1; i <= MAXV; i++) {
      if (c.scc[V(i)] == c.scc[V(-i)]) ok = false;
    }

    if (ok) l = m + 1;
    else r = m;
  }

  for (int i = 0; i < M; i++) {
    auto [op, u, v] = ops[i];
    if (op == 1) continue;

    if (i < l) cout << "YES DINNER\n";
    else cout << "NO DINNER\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
