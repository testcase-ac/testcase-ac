#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MAX = 1e9 + 7;
int cdist[1000];
vector<pii> graph[1000];

int main() {
  fast_io();

  int n, m, x, y, a, b, c;
  cin >> n >> m >> x >> y;

  while (m--) {
    cin >> a >> b >> c;
    graph[a].push_back({c, b});
    graph[b].push_back({c, a});
  }

  for (int i = 0; i < n; i++) cdist[i] = MAX;
  cdist[y] = 0;

  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.push({0, y});

  while (!pq.empty()) {
    auto[wi, ui] = pq.top();
    pq.pop();

    for (auto &p : graph[ui]) {
      auto[di, vi] = p;
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        pq.push({cdist[vi], vi});
      }
    }
  }

  sort(cdist, cdist + n);
  for (int i = 0; i < n; i++) cdist[i] *= 2;
  if (cdist[n - 1] > x) cout << -1;
  else {
    int ox = x, days = 1;
    for (int i = 0; i < n; i++) {
      if (cdist[i] > x) {
        days++;
        x = ox;
      }
      x -= cdist[i];
    }
    cout << days;
  }
  cout << '\n';
}
