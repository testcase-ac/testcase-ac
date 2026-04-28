#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 1e5, INF = 1e18;
int A[MAXN + 1];
vector<pair<int, int>> adj[MAXN + 1];
pair<ll, ll> cdist[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];
  int M; cin >> M;
  while (M--) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }
  int S, E; cin >> S >> E;

  using T = tuple<ll, ll, int>;
  priority_queue<T, vector<T>, greater<T>> pq;
  fill(cdist, cdist + N + 1, make_pair(INF, INF));
  pq.emplace(0, -A[S], S); cdist[S] = {0, -A[S]};

  while (!pq.empty()) {
    auto [dt, wt, v] = pq.top(); pq.pop();
    if (cdist[v] < make_pair(dt, wt)) continue;

    for (auto& [u, d] : adj[v]) {
      ll ndt = dt + d, nwt = wt - A[u];
      if (cdist[u] > make_pair(ndt, nwt)) {
        cdist[u] = {ndt, nwt};
        pq.emplace(ndt, nwt, u);
      }
    }
  }

  auto [edt, ewt] = cdist[E];
  if (edt == INF) cout << "-1\n";
  else cout << edt << ' ' << -ewt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
