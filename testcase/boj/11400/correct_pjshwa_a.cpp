#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
vector<int> adj[MAXN + 1];
int disc[MAXN + 1], t;
vector<pii> d_edges;

int dfs(int v, int p) {
  disc[v] = ++t;
  int ret = disc[v];

  for (auto& u : adj[v]) {
    if (u == p) continue;
    if (!disc[u]) {
      int low = dfs(u, v);
      if (low > disc[v]) {
        d_edges.emplace_back(min(u, v), max(u, v));
      }
      ret = min(ret, low);
    } else {
      ret = min(ret, disc[u]);
    }
  }

  return ret;
}

void solve() {
  int N, M; cin >> N >> M;
  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  for (int i = 1; i <= N; ++i) {
    if (!disc[i]) dfs(i, -1);
  }

  cout << d_edges.size() << '\n';
  sort(d_edges.begin(), d_edges.end());
  for (auto& e : d_edges) {
    cout << e.first << ' ' << e.second << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
