#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

const int MAX = 1000;
vector<int> graph[MAX + 1], gud[MAX + 1];

// 0: Not visited
// 1: Visited
// 2: Part of cycle
int vis[MAX + 1];

bool vis2[MAX + 1], vis3[MAX + 1];
bool d[MAX + 1][MAX + 1];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void dfs(int node) {
  int dst = graph[node][0];
  if (node == dst) vis[node] = 2;
  else {
    vis[node] = -1;

    // Cycle is detected
    if (vis[dst] == -1) {
      vis[dst] = 2;
      int s = graph[dst][0];
      while (s != dst) {
        vis[s] = 2;
        s = graph[s][0];
      }
    }
    else {
      if (!vis[dst]) dfs(dst);
      if (vis[node] != 2) vis[node] = 1;
    }
  }
}

int ccnt;
void dfs_cycle(int v) {
  vis2[v] = true;
  ccnt++;
  for (int u : graph[v]) {
    if (!vis2[u] && vis[u] == 2) dfs_cycle(u);
  }
}

int csz;
void dfs_component_size(int v) {
  vis3[v] = true;
  csz++;
  for (int u : gud[v]) {
    if (!vis3[u]) dfs_component_size(u);
  }
}

void solve() {
  int n, k;
  cin >> n >> k;

  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    graph[i].push_back(x);
    gud[i].push_back(x);
    gud[x].push_back(i);
  }

  for (int i = 1; i <= n; i++) {
    if (!vis[i]) dfs(i);
  }

  vector<pii> ad;
  for (int i = 1; i <= n; i++) {
    if (vis[i] == 2 && !vis2[i]) {
      ccnt = csz = 0;
      dfs_cycle(i);
      dfs_component_size(i);
      ad.push_back({ccnt, csz});
    }
  }

  d[0][0] = true;
  int sz = ad.size();
  for (int i = 1; i <= sz; i++) {
    auto [s, e] = ad[i - 1];
    for (int j = MAX; j >= 0; j--) d[i][j] = d[i - 1][j];
    for (int j = MAX; j >= 0; j--) for (int k = e; k >= s; k--) {
      if (j - k >= 0) d[i][j] |= d[i - 1][j - k];
    }
  }

  for (int j = k; j >= 0; j--) {
    if (d[sz][j]) return cout << j << '\n', void();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
