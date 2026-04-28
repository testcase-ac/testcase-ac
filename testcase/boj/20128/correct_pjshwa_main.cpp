#include <bits/stdc++.h>
typedef long long ll;
#define pll pair<ll, ll>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const ll INF = 4e18, MAXN = 2e5;
ll cdist[MAXN + 1];
vector<pll> graph[MAXN + 1];

void dijk(int s) {
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto[wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto[di, vi] = p;
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

int main() {
  fast_io();

  int n, m, u, v, w;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> u >> v >> w;
    if (w % 2) {
      graph[u].push_back({w, v + n});
      graph[v + n].push_back({w, u});
      graph[u + n].push_back({w, v});
      graph[v].push_back({w, u + n});
    }
    else {
      graph[u].push_back({w, v});
      graph[v].push_back({w, u});
      graph[u + n].push_back({w, v + n});
      graph[v + n].push_back({w, u + n});
    }
  }

  fill(cdist, cdist + 2 * n + 1, INF);
  dijk(1);
  for (int i = 1; i <= n; i++) {
    ll o = cdist[i + n] == INF ? -1 : cdist[i + n];
    ll e = cdist[i] == INF ? -1 : cdist[i];
    cout << o << ' ' << e << '\n';
  }
}
