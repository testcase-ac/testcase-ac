#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, INF = 0x3f3f3f3f;
vector<pii> adj[MAXN + 1];
int X[MAXN + 1], Y[MAXN + 1];
int cdist[MAXN + 1][MAXN + 1];

void solve() {
  int n, m; cin >> n >> m;
  for (int i = 1; i <= n; ++i) cin >> X[i] >> Y[i];
  while (m--) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  using T = tuple<int, int, int>;
  priority_queue<T, vector<T>, greater<T>> pq;

  memset(cdist, 0x3f, sizeof(cdist));
  pq.emplace(0, 0, 1); cdist[0][1] = 0;

  auto check_acute = [&](int o, int v1, int v2) -> bool {
    int dx1 = X[v1] - X[o], dy1 = Y[v1] - Y[o];
    int dx2 = X[v2] - X[o], dy2 = Y[v2] - Y[o];
    return dx1 * dx2 + dy1 * dy2 > 0;
  };

  while (!pq.empty()) {
    auto [di, pv, cv] = pq.top(); pq.pop();
    if (cdist[pv][cv] < di) continue;

    for (auto [nv, w] : adj[cv]) {
      int ndi = di + w;
      if (cdist[cv][nv] > ndi && (pv == 0 || !check_acute(cv, pv, nv))) {
        cdist[cv][nv] = ndi;
        pq.emplace(ndi, cv, nv);
      }
    }
  }

  int ans = INF;
  for (int i = 1; i <= n; ++i) ans = min(ans, cdist[i][2]);
  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
