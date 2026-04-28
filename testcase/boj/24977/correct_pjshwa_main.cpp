#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, INF = 1e9 + 7;
ll p[MAX + 1], v[MAX + 1], m;
int vis[MAX + 1];
bool vis2[MAX + 1];

void dfs(int u) {
  int dst = p[u];
  if (u == dst) vis[u] = 2;
  else {
    vis[u] = -1;

    // Cycle is detected
    if (vis[dst] == -1) {
      vis[dst] = 2;
      int s = p[dst];
      while (s != dst) {
        vis[s] = 2;
        s = p[s];
      }
    }
    else {
      if (!vis[dst]) dfs(dst);
      if (vis[u] != 2) vis[u] = 1;
    }
  }
}

void dfs2(int u) {
  vis2[u] = true;
  m = min(m, v[u]);
  if (!vis2[p[u]]) dfs2(p[u]);
}

void solve() {
  int n;
  cin >> n;

  ll ans = 0;
  for (int i = 1; i <= n; i++) cin >> p[i] >> v[i], ans += v[i];

  for (int i = 1; i <= n; i++) {
    if (!vis[i]) dfs(i);
  }

  for (int i = 1; i <= n; i++) {
    if (vis[i] == 2 && !vis2[i]) {
      m = INF;
      dfs2(i);
      ans -= m;
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
