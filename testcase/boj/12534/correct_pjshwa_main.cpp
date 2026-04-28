#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<int> graph[1000];
int vis[1000], deg[1000];

void dfs(int v, int cc) {
  vis[v] = cc;
  for (int d : graph[v]) if (!vis[d]) dfs(d, cc);
}

int main() {
  fast_io();

  int t;
  cin >> t;
  for (int tc = 1; tc <= t; tc++) {
    int v, e, a, b;
    cin >> v >> e;

    for (int i = 0; i < v; i++) graph[i].clear();
    memset(deg, 0, sizeof(deg));
    memset(vis, 0, sizeof(vis));

    while (e--) {
      cin >> a >> b;
      deg[a]++; deg[b]++;
      graph[a].push_back(b);
      graph[b].push_back(a);
    }

    int cc = 0;
    for (int i = 0; i < v; i++) if (!vis[i] && deg[i]) dfs(i, ++cc);

    map<int, vector<int>> cm;
    for (int i = 0; i < v; i++) if (deg[i]) cm[vis[i]].push_back(i);

    int ans;
    if (cm.size() == 1) {
      ans = 0;
      for (auto[cci, cv] : cm) {
        int oc = 0;
        for (int i : cv) if (deg[i] & 1) oc++;
        ans += oc / 2;
      }
    }
    else {
      ans = cm.size();
      for (auto[cci, cv] : cm) {
        int oc = 0;
        for (int i : cv) if (deg[i] & 1) oc++;
        ans += max(oc / 2 - 1, 0);
      }
    }
    
    cout << "Case #" << tc << ": " << ans << '\n';

  }
}
