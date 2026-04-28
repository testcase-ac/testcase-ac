#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 2e5, INF = 1e18;
vector<pii> adj[MAXN + 1];
ll cdist[MAXN + 1];

void solve() {
  int N, M, K; cin >> N >> M >> K;
  while (M--) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  using T = pair<ll, int>;
  priority_queue<T, vector<T>, greater<T>> pq;
  fill(cdist, cdist + N + 1, INF);
  cdist[1] = 0; pq.emplace(0, 1);
  
  while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (cdist[u] < d) continue;
    for (auto [v, w] : adj[u]) {
      if (cdist[v] > cdist[u] + w) {
        cdist[v] = cdist[u] + w;
        pq.emplace(cdist[v], v);
      }
    }
  }

  ll ans = INF, X; cin >> X;
  for (int i = 0; i < X; ++i) {
    int u; cin >> u;
    if (cdist[u] == INF) continue;
    ll turn = cdist[u] / K, val;
    if (turn % X == i) val = cdist[u];
    else {
      ll wturn = (i + X - turn % X) % X;
      val = (turn + wturn) * K;
    }
    ans = min(ans, val);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
