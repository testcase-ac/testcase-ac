#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 4000;
const ll INF = 1e18;
ll cdist[3 * MAX + 1];
vector<pll> graph[3 * MAX + 1];

void dijk(int s) {
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
    int a, b, c;
    cin >> a >> b >> c;
    graph[a].push_back({b, 2 * c});
    graph[b].push_back({a, 2 * c});
    graph[a + MAX].push_back({b + 2 * MAX, c});
    graph[b + MAX].push_back({a + 2 * MAX, c});
    graph[a + 2 * MAX].push_back({b + MAX, 4 * c});
    graph[b + 2 * MAX].push_back({a + MAX, 4 * c});
  }

  fill(cdist, cdist + 3 * MAX + 1, INF);
  dijk(1);
  dijk(1 + MAX);

  int ans = 0;
  for (int i = 2; i <= n; i++) {
    ll da = cdist[i], db = min(cdist[i + MAX], cdist[i + 2 * MAX]);
    if (da == INF || db == INF) continue;
    if (da < db) ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
