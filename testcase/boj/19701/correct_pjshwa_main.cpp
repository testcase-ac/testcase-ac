#include <bits/stdc++.h>
typedef long long ll;
#define pll pair<ll, ll>
using namespace std;

const int MAX = 2e5, bias = 1e5;
const ll INF = 1e14;
ll cdist[MAX + 1];
vector<pll> graph[MAX + 1];

void dijk(int s) {
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto[wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto[vi, di] = p;
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int v, e;
  cin >> v >> e;
  while (e--) {
    int x, y, t, k;
    cin >> x >> y >> t >> k;
    graph[x].push_back({y, t});
    graph[y].push_back({x, t});

    graph[x + bias].push_back({y + bias, t});
    graph[y + bias].push_back({x + bias, t});

    graph[x].push_back({y + bias, t - k});
    graph[y].push_back({x + bias, t - k});
  }

  fill(cdist, cdist + MAX + 1, INF);
  dijk(1);

  for (int i = 2; i <= v; i++) cout << cdist[i + bias] << '\n';
}
