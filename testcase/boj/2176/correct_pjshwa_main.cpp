#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
const ll INF = 1e18;
vector<tii> graph[MAX + 1];
bool use[2 * MAX + 1];
int d[MAX + 1];
ll cdist[MAX + 1];

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
      auto [vi, di, ei] = p;
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

int dfs(int v, int p) {
  if (d[v] != -1) return d[v];
  if (v == 2) return d[v] = 1;

  int res = 0;
  for (auto& [vi, di, ei] : graph[v]) {
    if (!use[ei] || vi == p) continue;
    res += dfs(vi, v);
  }

  return d[v] = res;
}

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back({v, w, i});
    graph[v].push_back({u, w, i + MAX});
  }

  dijk(2);
  for (int u = 1; u <= n; u++) {
    for (auto [v, w, e] : graph[u]) {
      if (cdist[v] < cdist[u]) use[e] = 1;
    }
  }

  memset(d, -1, sizeof(d));
  cout << dfs(1, -1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
