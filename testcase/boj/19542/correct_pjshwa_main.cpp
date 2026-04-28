#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
bool vis[MAX + 1];
int mdist[MAX + 1], d;

int dfs1(int v) {
  vis[v] = 1;

  int res = 0;
  for (int u : graph[v]) {
    if (!vis[u]) res = max(res, dfs1(u));
  }

  return mdist[v] = res + 1;
}

void dfs2(int v) {
  vis[v] = 1;
  for (int u : graph[v]) {
    if (!vis[u] && mdist[u] > d) dfs2(u);
  }
}

void solve() {
  int n, s;
  cin >> n >> s >> d;
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

  memset(vis, 0, sizeof(vis));
  dfs1(s);
  memset(vis, 0, sizeof(vis));
  dfs2(s);

  int cnt = 0;
  for (int i = 1; i <= n; i++) cnt += vis[i];
  cout << max(0, 2 * cnt - 2) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
