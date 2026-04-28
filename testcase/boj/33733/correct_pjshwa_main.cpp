#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
vector<int> adj[MAXN + 1];
int depth[MAXN + 1], outdegree[MAXN + 1], parent[MAXN + 1];

void dfs(int v, int l) {
  depth[v] = l;
  for (int u : adj[v]) dfs(u, l + 1);
}

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) {
    cin >> parent[i];
    adj[parent[i]].push_back(i);
    ++outdegree[parent[i]];
  }
  dfs(0, 0);

  int M = 0;
  for (int i = 1; i <= N; ++i) M += (outdegree[i] == 0);

  while (M--) {
    int u; cin >> u;
    while (u) {
      // cout << "u = " << u << ", parent = " << parent[u] << ", depth = " << depth[u] << '\n';
      if (--outdegree[parent[u]] > 0) break;
      u = parent[u];
    }
    cout << depth[u] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
