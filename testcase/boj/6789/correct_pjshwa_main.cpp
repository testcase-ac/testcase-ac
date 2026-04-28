#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

using T = tuple<int, int, int>;
const int MAXN = 1600, MAXS = 3600, INF = 0x3f3f3f3f;
int cdist[MAXN][MAXS + 1];
vector<T> adj[MAXN];

void solve() {
  int S, N, M; cin >> S >> N >> M;
  while (M--) {
    int u, v, w, a; cin >> u >> v >> w >> a;
    adj[u].emplace_back(v, w, a);
    adj[v].emplace_back(u, w, a);
  }

  memset(cdist, 0x3f, sizeof(cdist));
  priority_queue<T, vector<T>, greater<T>> pq;
  pq.emplace(0, 0, 0); cdist[0][0] = 0;

  while (!pq.empty()) {
    auto [d, u, s] = pq.top(); pq.pop();
    if (cdist[u][s] < d) continue;

    for (auto [v, w, a] : adj[u]) {
      int ns = a ? s + w : s;
      if (ns > S) continue;
      if (cdist[v][ns] > cdist[u][s] + w) {
        cdist[v][ns] = cdist[u][s] + w;
        pq.emplace(cdist[v][ns], v, ns);
      }
    }
  }

  int ans = INF;
  for (int i = 0; i <= S; ++i) ans = min(ans, cdist[N - 1][i]);
  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
