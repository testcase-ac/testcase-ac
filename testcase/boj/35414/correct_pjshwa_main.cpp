#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int vis[MAXN + 1];
vector<int> adj[MAXN + 1], V;

void dfs(int u) {
  vis[u] = 1;
  for (int v : adj[u]) {
    if (!vis[v]) dfs(v);
  }
  V.push_back(u);
}

void solve() {
  int N, M; cin >> N >> M;
  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v); adj[v].push_back(u);
  }

  vector<int> ans;
  for (int i = 1; i <= N; ++i) {
    if (vis[i]) continue;
    dfs(i);
    for (int e : V) if (e != i) ans.push_back(e);
    V.clear();
  }

  cout << ans.size() << '\n';
  for (int u : ans) cout << u << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
