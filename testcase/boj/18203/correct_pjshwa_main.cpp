#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
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
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back({v, w});
    graph[v].push_back({u, w});
  }

  vector<int> V(7); int p[7];
  for (int i = 0; i < 7; i++) cin >> V[i], p[i] = i;

  vector<vector<ll>> dists(7, vector<ll>(n + 1));
  for (int i = 0; i < 7; i++) {
    dijk(V[i]);
    for (int j = 1; j <= n; j++) dists[i][j] = cdist[j];
  }
  dijk(1);

  ll ans = INF;
  do {
    ll cur = cdist[V[p[0]]];
    for (int i = 0; i < 6; i++) cur += dists[p[i]][V[p[i + 1]]];
    ans = min(ans, cur);
  } while (next_permutation(p, p + 7));

  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
