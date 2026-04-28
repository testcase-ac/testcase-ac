#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
const ll INF = 1e18;
ll cdist[MAX + 1];
vector<pll> graph[MAX + 1];

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  while (m--) {
    int u, v, c;
    cin >> u >> v >> c;
    graph[v].push_back({u, c});
  }

  fill(cdist, cdist + MAX + 1, INF);
  priority_queue<pll, vector<pll>, greater<pll>> pq;

  while (k--) {
    int s;
    cin >> s;
    cdist[s] = 0;
    pq.push({0, s});
  }

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

  ll cur = 0, cv = 0;
  for (int i = 1; i <= n; i++) {
    if (cdist[i] > cur) cur = cdist[i], cv = i;
  }
  cout << cv << '\n' << cur << '\n';
}

int main() {
  fast_io();
  
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
