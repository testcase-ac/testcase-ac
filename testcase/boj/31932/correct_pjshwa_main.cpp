#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 1e5, INF = 1e18;
vector<tuple<int, int, int>> adj[MAXN];
ll cdist[MAXN], N;

void dijk(int m) {
  fill(cdist, cdist + N, INF);
  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.emplace(m, 0); cdist[0] = m;

  while (!pq.empty()) {
    auto [cost, u] = pq.top(); pq.pop();
    if (cost > cdist[u]) continue;

    for (auto& [v, d, t] : adj[u]) {
      ll ncost = cost + d;
      if (ncost <= t && cdist[v] > ncost) {
        cdist[v] = ncost;
        pq.emplace(cdist[v], v);
      }
    }
  }
}

void solve() {
  int M; cin >> N >> M;
  while (M--) {
    int u, v, d, t; cin >> u >> v >> d >> t; --u; --v;
    adj[u].emplace_back(v, d, t);
    adj[v].emplace_back(u, d, t);
  }

  int l = 0, r = 1e9 + 1;
  while (l < r) {
    int m = (l + r) / 2;
    dijk(m);
    if (cdist[N - 1] == INF) r = m;
    else l = m + 1;
  }
  cout << l - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
