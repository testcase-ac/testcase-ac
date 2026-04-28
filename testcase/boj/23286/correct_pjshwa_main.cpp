#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 300;
const ll INF = 1e18;
ll cdist[MAX + 1];
vector<pll> graph[MAX + 1];

void dijk(int s) {
  fill(cdist, cdist + MAX + 1, INF);
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto [vi, di] = p;
      ll ndist = max(di, cdist[ui]);
      if (cdist[vi] > ndist) {
        cdist[vi] = ndist;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

void solve() {
  int N, M, Q;
  cin >> N >> M >> Q;

  while (M--) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back({v, w});
  }

  vector<ll> ans(Q);
  vector<tuple<int, int, int>> queries(Q);
  for (int i = 0; i < Q; i++) {
    int u, v;
    cin >> u >> v;
    queries[i] = {u, v, i};
  }
  sort(queries.begin(), queries.end());

  int last = -1;
  for (int i = 0; i < Q; i++) {
    auto& [u, v, j] = queries[i];
    if (u != last) {
      dijk(u);
      last = u;
    }
    ans[j] = cdist[v];
  }

  for (auto a : ans) {
    if (a == INF) cout << -1 << '\n';
    else cout << a << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
