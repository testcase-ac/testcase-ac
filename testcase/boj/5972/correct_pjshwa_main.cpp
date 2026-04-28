#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50000, INF = 1e9 + 7;
int cdist[MAX + 1];
vector<pii> graph[MAX + 1];

int main() {
  fast_io();

  int v, e, ui, vi, wi, di;
  cin >> v >> e;

  while (e--) {
    cin >> ui >> vi >> wi;
    graph[ui].push_back({wi, vi});
    graph[vi].push_back({wi, ui});
  }

  for (int i = 1; i <= v; i++) cdist[i] = INF;
  cdist[1] = 0;

  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.push({0, 1});

  while (!pq.empty()) {
    tie(wi, ui) = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      tie(di, vi) = p;
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        pq.push({cdist[vi], vi});
      }
    }
  }

  cout << cdist[v] << '\n';
}
