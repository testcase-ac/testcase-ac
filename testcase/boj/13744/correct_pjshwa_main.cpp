#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2000, BIAS = 1000;

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
  int N, R, L; cin >> N >> R >> L;

  vector<pii> points(L + 1);
  for (int i = 1; i <= L; ++i) {
    int x, y; cin >> x >> y;
    points[i] = {x, y};
  }

  SCC c(MAXN);
  for (int i = 1; i <= L; ++i) for (int j = i + 1; j <= L; ++j) {
    if (i == j) continue;
    auto [x1, y1] = points[i]; auto [x2, y2] = points[j];
    if (x1 == x2 && abs(y1 - y2) <= 2 * R - 2) {
      c.add_edge(V(i), V(-j));
      c.add_edge(V(j), V(-i));
    }
    if (y1 == y2 && abs(x1 - x2) <= 2 * R - 2) {
      c.add_edge(V(-i), V(j));
      c.add_edge(V(-j), V(i));
    }
  }
  c.perform();

  bool ok = true;
  for (int i = 1; i <= L; i++) {
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
