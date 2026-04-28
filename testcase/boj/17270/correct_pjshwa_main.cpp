#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
const ll INF = 1e14;
ll cdist[2][MAX + 1];
vector<pll> graph[MAX + 1];
int v;

void dijk(int d, int s) {
  for (int i = 1; i <= v; i++) cdist[d][i] = INF;
  cdist[d][s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[d][ui]) continue;

    for (auto &p : graph[ui]) {
      auto [vi, di] = p;
      if (cdist[d][vi] > di + wi) {
        cdist[d][vi] = di + wi;
        pq.push({cdist[d][vi], vi});
      }
    }
  }
}

int main() {
  fast_io();

  int e;
  cin >> v >> e;

  while (e--) {
    int ui, vi, wi;
    cin >> ui >> vi >> wi;
    graph[ui].push_back({vi, wi});
    graph[vi].push_back({ui, wi});
  }

  int j, s;
  cin >> j >> s;
  dijk(0, j);
  dijk(1, s);

  ll mdist = INF, jdist = INF, mi = -1;
  for (int i = 1; i <= v; i++) {
    if (i == j || i == s) continue;
    mdist = min(mdist, cdist[0][i] + cdist[1][i]);
  }
  for (int i = 1; i <= v; i++) {
    if (i == j || i == s) continue;
    if (mdist != cdist[0][i] + cdist[1][i]) continue;
    if (cdist[0][i] > cdist[1][i]) continue;

    if (jdist > cdist[0][i]) {
      jdist = cdist[0][i];
      mi = i;
    }
  }
  cout << mi << '\n';
}
