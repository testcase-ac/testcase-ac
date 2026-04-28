#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<int> graph[1001];
int vis[1001], deg[1001];

void dfs(int v, int cc) {
  vis[v] = cc;
  for (int d : graph[v]) if (!vis[d]) dfs(d, cc);
}

int main() {
  fast_io();

  int v, e, a, b;
  cin >> v >> e;
  while (e--) {
    cin >> a >> b;
    deg[a]++; deg[b]++;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  int cc = 0;
  for (int i = 1; i <= v; i++) if (!vis[i]) dfs(i, ++cc);

  map<int, vector<int>> cm;
  for (int i = 1; i <= v; i++) cm[vis[i]].push_back(i);

  int ans = cm.size() - 1;
  for (auto[cci, cv] : cm) {
    int oc = 0;
    for (int i : cv) if (deg[i] & 1) oc++;
    assert(oc % 2 == 0);
    ans += max(oc / 2 - 1, 0);
  }

  cout << ans;
}
