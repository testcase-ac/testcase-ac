#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using pllpl = pair<pll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e5, MOD = 1e9 + 9;
const ll INF = 1e18;
pll cdist[MAX + 1];
int par[MAX + 1];
vector<pll> graph[MAX + 1];

void dijk(int s) {
  for (int i = 0; i <= MAX; i++) cdist[i] = {INF, INF};
  cdist[s] = {0, 0};
  par[s] = 1;

  priority_queue<pllpl, vector<pllpl>, greater<pllpl>> pq;
  pq.push({{0, 0}, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;
    auto [cd, cw] = wi;

    for (auto &p : graph[ui]) {
      auto [vi, di] = p;
      pll nwi = {di + cd, cw + 1};
      if (cdist[vi] > nwi) {
        cdist[vi] = nwi;
        par[vi] = par[ui];
        pq.push({nwi, vi});
      }
      else if (cdist[vi] == nwi) {
        par[vi] = (par[vi] + par[ui]) % MOD;
      }
    }
  }
}

void solve() {
  int N, M, x, y;
  cin >> N >> M >> x >> y;
  while (M--) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back({v, w});
  }

  dijk(x);
  auto [ed, ew] = cdist[y];
  if (ed == INF) cout << "-1\n";
  else {
    cout << ed << '\n' << ew << '\n' << par[y] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
