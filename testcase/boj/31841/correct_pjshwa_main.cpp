#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5, MAXM = 3e5;
vector<pii> adj[MAXN + 1];
bool vis[MAXN + 1];
int D[MAXM + 1], cur = 0;

void dfs(int v) {
  vis[v] = true;
  for (auto& [u, i] : adj[v]) {
    if (D[i] == -1) D[i] = ++cur;
    if (!vis[u]) dfs(u);
  }
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= M; ++i) {
    int u, v; cin >> u >> v;
    adj[u].emplace_back(v, i); adj[v].emplace_back(u, i);
  }

  memset(D, -1, sizeof(D));
  dfs(1);
  assert(cur == M);
  for (int v = 1; v <= N; ++v) {
    for (auto& [u, i] : adj[v]) {
      if (D[i] == -1) continue;
      cout << u << ' ' << v << ' ' << D[i] << '\n';
      D[i] = -1;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
