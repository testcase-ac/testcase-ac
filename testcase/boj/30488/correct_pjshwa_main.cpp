#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 1e5, INF = 1e18;
vector<pii> adj[MAXN + 1];
ll cdist[MAXN + 1][2];

void solve() {
  int N, M, P, G; cin >> N >> M >> P >> G;
  while (M--) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  using T = tuple<ll, int, int>;
  priority_queue<T, vector<T>, greater<T>> pq;
  for (int i = 1; i <= N; ++i) cdist[i][0] = cdist[i][1] = INF;
  pq.emplace(0, P, 0); cdist[P][0] = 0;

  while (!pq.empty()) {
    auto [d, u, g] = pq.top(); pq.pop();
    if (cdist[u][g] < d) continue;

    for (auto [v, w] : adj[u]) {
      ll nd = d + w, ng = (g == 1 || v == G);
      if (cdist[v][ng] > nd) {
        cdist[v][ng] = nd;
        pq.emplace(nd, v, ng);
      }
    }
  }

  vector<int> ans;
  for (int i = 1; i <= N; ++i) {
    if (cdist[i][1] == INF) continue;
    if (cdist[i][0] <= cdist[i][1]) continue;
    if (cdist[i][1] == 2 * cdist[G][1]) ans.push_back(i);
  }

  if (ans.empty()) cout << "*\n";
  else {
    for (int v : ans) cout << v << ' '; cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
