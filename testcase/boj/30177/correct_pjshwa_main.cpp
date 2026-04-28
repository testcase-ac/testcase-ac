#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
vector<int> adj[MAXN];
int deg[MAXN], D[MAXN], min_val, max_val;

void dfs1(int v, int p) {
  for (int u : adj[v]) {
    if (u == p) continue;
    D[u] = D[v] ^ 1;
    dfs1(u, v);
  }
}

void dfs2(int v, int p) {
  int cnt = 0;
  for (int u : adj[v]) {
    if (u == p) continue;
    if (deg[u] == 1) ++cnt;
    else dfs2(u, v);
  }
  if (cnt > 1) max_val -= cnt - 1;
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N - 1; ++i) {
    int u, v; cin >> u >> v; --u; --v;
    adj[u].push_back(v); adj[v].push_back(u);
    ++deg[u]; ++deg[v];
  }

  int root;
  for (root = 0; root < N; ++root) {
    if (deg[root] != 1) break;
  }

  dfs1(root, -1); set<int> U;
  for (int i = 0; i < N; ++i) {
    if (deg[i] == 1) U.insert(D[i]);
  }
  min_val = 2 * U.size() - 1;

  max_val = N - 1;
  dfs2(root, -1);
  cout << min_val << ' ' << max_val << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
