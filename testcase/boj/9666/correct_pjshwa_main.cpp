#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
vector<pii> adj[MAX + 1];
int color[MAX + 1];
bool is_bipartite;

void dfs(int v, int c, int l) {
  color[v] = c;
  for (auto [u, i] : adj[v]) {
    if (i > l) continue;
    if (color[u] == -1) dfs(u, 3 - c, l);
    else if (color[u] == c) is_bipartite = false;
  }
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= M; ++i) {
    int u, v; cin >> u >> v;
    adj[u].emplace_back(v, i);
    adj[v].emplace_back(u, i);
  }

  int l = 1, r = M + 1;
  while (l < r) {
    int m = (l + r) / 2;

    memset(color, -1, sizeof(color));
    is_bipartite = true;
    for (int i = 1; i <= N; ++i) {
      if (color[i] == -1) dfs(i, 0, m);
    }

    if (is_bipartite) l = m + 1;
    else r = m;
  }
  cout << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
