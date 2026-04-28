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
int n, m;

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
      ll diff = di - (wi % m), nwi;
      if (diff >= 0) nwi = wi + diff;
      else nwi = wi + m + diff;
      if (cdist[vi] > nwi + 1) {
        cdist[vi] = nwi + 1;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

int main() {
  fast_io();

  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back({b, i});
    graph[b].push_back({a, i});
  }

  dijk(1);
  cout << cdist[n] << '\n';
}
