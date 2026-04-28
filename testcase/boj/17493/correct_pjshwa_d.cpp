#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int ans = 0;
vector<int> graph[MAX + 1];
bool vis[MAX + 1];

// Returns 0, 1 or 2
// 0 means ad is not installed on this node and ad cannot be accessed from adjacent nodes (yet)
// 1 means ad is not installed on this node but ad can be accessed from adjacent nodes
// 2 means ad is installed on this node
int dfs(int v) {
  vis[v] = true;

  bool need = false, accessible = false;
  for (int d : graph[v]) {
    if (vis[d]) continue;

    int res = dfs(d);
    if (res == 0) need = true;
    if (res == 2) accessible = true;
  }

  if (need) {
    ans++;
    return 2;
  }
  if (accessible) return 1;
  return 0;
}

int main() {
  fast_io();

  int n, m, a, b;
  cin >> n >> m;

  while (m--) {
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      if (dfs(i) == 0) ans++;
    }
  }
  cout << ans;
}
