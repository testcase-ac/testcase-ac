#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5, BIAS = 1e5;
int D[MAXN + 1];
vector<int> C[MAXN + 1];

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
  int N, M; cin >> N >> M;
  for (int i = 1; i <= N; ++i) cin >> D[i];
  for (int i = 1; i <= M; ++i) {
    int k; cin >> k;
    while (k--) {
      int x; cin >> x;
      C[x].push_back(i);
    }
  }

  SCC c(MAXN);
  for (int i = 1; i <= N; ++i) {
    int u = C[i][0], v = C[i][1];
    if (D[i]) {
      c.add_edge(V(u), V(v));
      c.add_edge(V(v), V(u));
      c.add_edge(V(-u), V(-v));
      c.add_edge(V(-v), V(-u));
    } else {
      c.add_edge(V(-u), V(v));
      c.add_edge(V(-v), V(u));
      c.add_edge(V(u), V(-v));
      c.add_edge(V(v), V(-u));
    }
  }
  c.perform();

  bool ok = true;
  for (int i = 1; i <= M; ++i) {
    if (c.scc[V(i)] == c.scc[V(-i)]) ok = false;
  }
  cout << ok << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
