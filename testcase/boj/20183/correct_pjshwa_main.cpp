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
ll maxs;

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
      if (di > maxs) continue;

      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

void solve() {
  int n, m, a, b;
  ll c;
  cin >> n >> m >> a >> b >> c;

  while (m--) {
    int x, y, w;
    cin >> x >> y >> w;
    graph[x].push_back({y, w});
    graph[y].push_back({x, w});
  }

  ll left = 1, right = INF;
  while (left < right) {
    maxs = (left + right) / 2;
    dijk(a);

    if (cdist[b] > c) left = maxs + 1;
    else right = maxs;
  }

  if (left == INF) cout << "-1\n";
  else cout << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
