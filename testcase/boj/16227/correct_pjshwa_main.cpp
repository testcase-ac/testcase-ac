#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 151515;
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
    int u, v, t;
    cin >> u >> v >> t;
    if (t > 100) continue;
    for (int c = 0; c <= 100; c++) {
      if (c + t <= 100) {
        graph[u * 101 + c].push_back({v * 101 + c + t, t});
        graph[v * 101 + c].push_back({u * 101 + c + t, t});
      }
      graph[u * 101 + c].push_back({v * 101 + t, t + 5});
      graph[v * 101 + c].push_back({u * 101 + t, t + 5});
    }
  }
  dijk(0);
  ll ans = INF;
  for (int c = 0; c <= 100; c++) ans = min(ans, cdist[(n + 1) * 101 + c]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
