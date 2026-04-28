#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
vector<int> adj[MAXN + 1], radj[MAXN + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= N; i++) {
    adj[i].clear(); radj[i].clear();
  }

  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v); radj[v].push_back(u);
  }

  int H = (N + 1) / 2, ans = 0;
  for (int i = 1; i <= N; i++) {
    queue<int> q;
    bool f = false;
    for (auto& g : {adj, radj}) {
      vector<bool> vis(N + 1);
      q.push(i); vis[i] = true;

      while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
          if (!vis[v]) vis[v] = true, q.push(v);
        }
      }

      int cnt = accumulate(vis.begin() + 1, vis.end(), 0);
      if (cnt > H) f = true;
    }

    if (f) ans++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
