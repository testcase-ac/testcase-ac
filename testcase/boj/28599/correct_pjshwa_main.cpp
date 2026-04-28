#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 2e5, INF = 5e18;
vector<pii> adj[MAXN + 1];
ll cdist[MAXN + 1], U[MAXN + 1];

void dijk(int s) {
  fill(cdist, cdist + MAXN + 1, INF);
  cdist[s] = 0;
  using T = pair<ll, int>;
  priority_queue<T, vector<T>, greater<T>> pq;
  pq.emplace(0, s);
  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (cdist[u] < d) continue;
    for (auto [v, w] : adj[u]) {
      if (cdist[v] > cdist[u] + w) {
        cdist[v] = cdist[u] + w;
        pq.emplace(cdist[v], v);
      }
    }
  }
}

void solve() {
  int N, M, K, S, V; cin >> N >> M >> K;
  while (M--) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }
  dijk(1);

  cin >> S;
  vector<tuple<int, int, int>> machines(S);
  for (auto& [v, h, t] : machines) cin >> v >> h >> t;

  cin >> V;
  ll l = 1, r = INF;

  while (l < r) {
    ll m = (l + r) / 2, ui = 0;
    for (int j = 0; j < S; ++j) {
      auto [v, h, t] = machines[j];
      if (cdist[v] == INF) U[ui++] = 0;
      else {
        ll rem = max(0LL, m - 2 * cdist[v] - h);
        U[ui++] = rem / t;
      }
    }
    sort(U, U + ui, greater<ll>());

    __int128_t sum = 0;
    for (int i = 0; i < K; ++i) sum += U[i];

    if (sum < V) l = m + 1;
    else r = m;
  }

  cout << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
