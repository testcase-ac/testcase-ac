#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 2e5, INF = 1e18;
vector<pii> adj[MAXN + 1];
ll cdist[MAXN + 1], edist[MAXN + 1];
bool vis[MAXN + 1];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 0; i < N - 1; ++i) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  using T = pair<ll, int>;
  priority_queue<T, vector<T>, greater<T>> pq;
  fill(edist, edist + N + 1, INF);

  while (K--) {
    int e; cin >> e;
    edist[e] = 0; pq.push({0, e});
  }
  while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (edist[u] < d) continue;
    for (auto [v, w] : adj[u]) {
      if (edist[v] > d + w) {
        edist[v] = d + w;
        pq.push({edist[v], v});
      }
    }
  }

  fill(cdist, cdist + N + 1, INF);
  cdist[1] = 0; pq.push({0, 1});
  while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (cdist[u] < d) continue;
    for (auto [v, w] : adj[u]) {
      if (cdist[v] > d + w) {
        cdist[v] = d + w;
        pq.push({cdist[v], v});
      }
    }
  }

  ll ans = 0;
  queue<int> q;
  q.push(1); vis[1] = true;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    ans = max(ans, edist[u]);
    for (auto [v, w] : adj[u]) {
      if (!vis[v] && cdist[v] < edist[v]) vis[v] = true, q.push(v);
      else {
        ll d = (w - edist[u] + edist[v]) / 2;
        ans = max(ans, d + edist[u]);
      }
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
