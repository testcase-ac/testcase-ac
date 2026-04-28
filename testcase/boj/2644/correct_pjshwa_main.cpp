#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100, INF = 1e9 + 7;
vector<int> graph[MAX + 1];
int cdist[MAX + 1];

void solve() {
  int n, x, y, m;
  cin >> n >> x >> y >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  fill(cdist, cdist + n + 1, INF);
  queue<pii> q;
  cdist[x] = 0;
  q.push({x, 0});

  while (!q.empty()) {
    auto [u, d] = q.front();
    q.pop();
    if (d > cdist[u]) continue;
    for (int v : graph[u]) {
      if (cdist[v] > d + 1) {
        cdist[v] = d + 1;
        q.push({v, d + 1});
      }
    }
  }

  if (cdist[y] == INF) cout << "-1\n";
  else cout << cdist[y] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
