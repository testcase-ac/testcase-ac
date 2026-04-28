#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, INF = 1e9 + 7;
set<int> graph[MAX + 1];
int order[MAX + 1], cdist[MAX + 1];
bool vis[MAX + 1];

void bfs(int s) {
  memset(vis, 0, sizeof(vis));
  queue<pii> q;
  q.push({s, 0});
  vis[s] = true;

  int it = 0;
  while (!q.empty()) {
    auto [v, c] = q.front();
    q.pop();

    order[v] = ++it;
    cdist[v] = c;

    for (int d : graph[v]) {
      if (!vis[d]) vis[d] = true, q.push({d, c + 1});
    }
  }
}

void solve() {
  int n, m, r;
  cin >> n >> m >> r;
  while (m--) {
    int u, v;
    cin >> u >> v;
    graph[u].insert(v);
    graph[v].insert(u);
  }

  bfs(r);
  ll ans = 0;
  for (int i = 1; i <= n; i++) ans += (ll)order[i] * cdist[i];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
