#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
vector<pii> adj[MAXN + 1][2];
bool vis[MAXN + 1][2];
int zcnt = 0, tcnt = 0;

void dfs(int u, int j) {
  ++tcnt;
  zcnt += j == 0;
  vis[u][j] = true;

  for (auto& [v, c] : adj[u][j]) {
    if (vis[v][c]) continue;
    vis[v][c] = true;
    dfs(v, c);
  }
}

void solve() {
  int N; cin >> N;
  for (int u = 1; u <= N; ++u) {
    int v, c; cin >> v >> c;
    for (int j = 0; j < 2; ++j) {
      adj[u][j].emplace_back(v, j ^ c);
      adj[v][j ^ c].emplace_back(u, j);
    }
  }

  int ans = 0;
  for (int u = 1; u <= N; ++u) {
    if (vis[u][0] || vis[u][1]) continue;
    zcnt = tcnt = 0;

    dfs(u, 0);
    assert(!vis[u][1]);

    ans += min(zcnt, tcnt - zcnt);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
