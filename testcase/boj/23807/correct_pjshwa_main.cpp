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

int main() {
  fast_io();

  int v, e;
  cin >> v >> e;

  while (e--) {
    int ui, vi, wi;
    cin >> ui >> vi >> wi;
    graph[ui].push_back({vi, wi});
    graph[vi].push_back({ui, wi});
  }

  int x, z, p;
  cin >> x >> z >> p;

  vector<ll> points(p), dists_s(p), dists_e(p);
  vector<vector<ll>> dists(p, vector<ll>(v + 1));
  for (int i = 0; i < p; i++) cin >> points[i];

  dijk(x);
  for (int i = 0; i < p; i++) dists_s[i] = cdist[points[i]];
  dijk(z);
  for (int i = 0; i < p; i++) dists_e[i] = cdist[points[i]];

  for (int pi = 0; pi < p; pi++) {
    dijk(points[pi]);
    for (int i = 1; i <= v; i++) dists[pi][i] = cdist[i];
  }

  ll ans = INF;
  for (int pi = 0; pi < p; pi++) for (int pj = 0; pj < p; pj++) for (int pk = 0; pk < p; pk++) {
    if (pi == pj || pi == pk || pj == pk) continue;
    ans = min(ans, dists_s[pi] + dists_e[pk] + dists[pi][points[pj]] + dists[pj][points[pk]]);
  }

  if (ans >= INF) cout << "-1\n";
  else cout << ans << '\n';
}
