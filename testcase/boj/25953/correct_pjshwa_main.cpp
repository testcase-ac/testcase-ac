#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int n, t, m, s, e; cin >> n >> t >> m >> s >> e;

  int cdist[n + 1];
  memset(cdist, 0x3f, sizeof(cdist)); cdist[s] = 0;

  for (int i = 1; i <= t; ++i) {
    int ndist[n + 1];
    for (int j = 1; j <= n; ++j) ndist[j] = cdist[j];

    for (int j = 0; j < m; ++j) {
      int u, v, w; cin >> u >> v >> w;
      ndist[v] = min(ndist[v], cdist[u] + w);
      ndist[u] = min(ndist[u], cdist[v] + w);
    }

    for (int j = 1; j <= n; ++j) cdist[j] = ndist[j];
  }

  if (cdist[e] == INF) cout << "-1\n";
  else cout << cdist[e] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
