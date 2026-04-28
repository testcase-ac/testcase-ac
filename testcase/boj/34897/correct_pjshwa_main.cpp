#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
vector<pii> adj[MAXN][2];
bool vis[MAXN][2];

void dfs(int v, int s) {
  vis[v][s] = true;
  for (auto [u, ns] : adj[v][s]) {
    if (!vis[u][ns]) dfs(u, ns);
  }
}

void solve() {
  int N, M; cin >> N >> M;
  while (M--) {
    int op, u, v; cin >> op >> u >> v; --u; --v;
    if (op == 1) {
      for (int i = u; i <= v; ++i) {
        int j = u + v - i;
        adj[i][0].emplace_back(j, 0);
        adj[i][1].emplace_back(j, 1);
      }
    } else {
      for (int s = 0; s < 2; ++s) {
        adj[u][s].emplace_back(v, s ^ 1);
        adj[v][s].emplace_back(u, s ^ 1);
      }
    }
  }

  for (int i = 0; i < N; ++i) {
    if (vis[i][0] || vis[i][1]) continue;
    dfs(i, 0);
    if (vis[i][1]) return cout << "No\n", void();
  }

  cout << "Yes\n";
  for (int i = 0; i < N; ++i) cout << (char)(vis[i][0] + 'A');
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
