#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000, INF = 1e9 + 7;
vector<int> graph[MAX + 1];
int greach[MAX + 1][MAX + 1];
int C[MAX + 1], R[MAX + 1];
bool vis[MAX + 1];
int cdist[MAX + 1];
int N;

// O(V^2) dijkstra
void dijk(int s) {
  fill(cdist, cdist + N + 1, INF);
  memset(vis, 0, sizeof(vis));
  cdist[s] = 0;

  for (int it = 1; it <= N - 1; it++) {
    ll md = INF, mi = -1;
    for (int vi = 1; vi <= N; vi++) {
      if (!vis[vi] && cdist[vi] <= md) {
        md = cdist[vi];
        mi = vi;
      }
    }

    vis[mi] = true;
    for (int vi = 1; vi <= N; vi++) {
      if (vis[vi]) continue;
      if (greach[mi][vi] == -1) continue;
      if (cdist[mi] + greach[mi][vi] < cdist[vi]) {
        cdist[vi] = cdist[mi] + greach[mi][vi];
      }
    }
  }
}

void solve() {
  int M;
  cin >> N >> M;
  for (int i = 1; i <= N; i++) cin >> C[i] >> R[i];

  while (M--) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  memset(greach, -1, sizeof(greach));
  for (int i = 1; i <= N; i++) {
    memset(vis, 0, sizeof(vis));

    queue<pii> q;
    q.push({i, 0});
    vis[i] = true;

    while (!q.empty()) {
      auto [u, d] = q.front();
      q.pop();
      
      if (d == R[i]) continue;

      for (auto v : graph[u]) {
        if (vis[v]) continue;
        vis[v] = true;
        q.push({v, d + 1});
      }
    }

    for (int j = 1; j <= N; j++) {
      if (i != j && vis[j]) greach[i][j] = C[i];
    }
  }

  dijk(1);
  cout << cdist[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
