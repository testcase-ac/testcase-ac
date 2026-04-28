#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
vector<pii> graph[MAX + 1];
int cdist[MAX + 1];

void bfs(int v, int b) {
  fill(cdist, cdist + MAX + 1, INF);

  queue<int> q;
  q.push(v);
  cdist[v] = 0;

  while (!q.empty()) {
    int u = q.front(); q.pop();

    for (auto [w, c] : graph[u]) {
      if (c < b) continue;
      if (cdist[w] == INF) {
        cdist[w] = cdist[u] + 1;
        q.push(w);
      }
    }
  }
}

void solve() {
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  for (int i = 1; i <= n; i++) graph[i].clear();

  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back({v, w});
    graph[v].push_back({u, w});
  }

  int left = 1, right = 1e5 + 1;
  while (left < right) {
    int mid = (left + right) / 2;
    bfs(s, mid);

    if (cdist[t] == INF) right = mid;
    else left = mid + 1;
  }

  cout << left - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
