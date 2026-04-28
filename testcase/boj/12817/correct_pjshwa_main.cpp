#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
vector<int> graph[MAX + 1];
ll sz[MAX + 1], ans[MAX + 1];

void dfs1(int v, int p) {
  for (int u : graph[v]) {
    if (u == p) continue;

    dfs1(u, v);
    ans[v] += 2 * sz[v] * sz[u];
    sz[v] += sz[u];
  }
  sz[v]++;
}

void dfs2(int v, int p, int pcnt) {
  int csz = 0;
  for (int u : graph[v]) {
    if (u == p) continue;
    csz += sz[u];
  }
  for (int u : graph[v]) {
    if (u == p) continue;
    dfs2(u, v, pcnt + 1 + csz - sz[u]);
  }
  ans[v] += 2 * pcnt * (sz[v] - 1);
}

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  dfs1(1, 0);
  dfs2(1, 0, 0);
  for (int i = 1; i <= N; i++) cout << (ans[i] + 2 * (N - 1)) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
