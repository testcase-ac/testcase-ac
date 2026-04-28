#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
using namespace std;

bool visited[500];
pii points[500];
vector<pii> graph[500];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int dist(pii point1, pii point2) {
  return (point2.first - point1.first) * (point2.first - point1.first) +\
  (point2.second - point1.second) * (point2.second - point1.second);
}

void solve() {
  int p, x, y, d;
  memset(visited, false, sizeof(visited));
  cin >> p;

  for (int i = 0; i < p; i++) {
    cin >> x >> y;
    points[i] = {x, y};
  }

  for (int i = 0; i < p; i++) {
    for (int j = i + 1; j < p; j++) {
      d = dist(points[i], points[j]);
      graph[i].push_back({d, j});
      graph[j].push_back({d, i});
    }
  }

  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.push({0, 0});

  // Prim's algorithm
  ll ans = 0;
  int wgt, vtx, wgt_d, vtx_d;
  while (!pq.empty()) {
    tie(wgt, vtx) = pq.top();
    pq.pop();

    if (visited[vtx]) continue;
    visited[vtx] = true;
    ans += wgt;

    for (auto &x : graph[vtx]) {
      tie(wgt_d, vtx_d) = x;
      if (!visited[vtx_d]) pq.push({wgt_d, vtx_d});
    }
  }

  cout << ans << '\n';

}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
