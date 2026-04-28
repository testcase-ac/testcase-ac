#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3e5;
vector<pii> graph[MAX + 1];
ll d1[MAX + 1], d2[MAX + 1], sz[MAX + 1];

ll dfs1(int v, int p) {
  sz[v] = 1;
  for (auto [u, w] : graph[v]) {
    if (u == p) continue;
    d1[v] += dfs1(u, v) + w * sz[u];
    sz[v] += sz[u];
  }
  return d1[v];
}

void dfs2(int v, int p, ll h) {
  d2[v] = h;
  for (auto [u, w] : graph[v]) {
    if (u == p) continue;
    dfs2(u, v, h + w * (sz[1] - 2 * sz[u]));
  }
}

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N - 1; i++) {
    int u, v, d;
    cin >> u >> v >> d;
    graph[u].emplace_back(v, d);
    graph[v].emplace_back(u, d);
  }

  dfs1(1, 0);
  dfs2(1, 0, d1[1]);
  for (int i = 1; i <= N; i++) cout << d2[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
