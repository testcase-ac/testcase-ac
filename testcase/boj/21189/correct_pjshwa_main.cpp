#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, INF = 0x3f3f3f3f;
vector<int> graph[MAX + 1];
int cdist[MAX + 1];

void solve() {
  int N, M;
  cin >> N >> M;
  while (M--) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  memset(cdist, INF, sizeof(cdist));
  
  queue<pii> q;
  q.push({1, 0});
  cdist[1] = 0;

  while (!q.empty()) {
    auto [v, c] = q.front(); q.pop();

    for (auto &u : graph[v]) {
      if (cdist[u] > c + 1) {
        cdist[u] = c + 1;
        q.push({u, c + 1});
      }
    }
  }

  cout << cdist[N] - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
