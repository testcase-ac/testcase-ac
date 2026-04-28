#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int vis[MAX + 1], vis2[MAX + 1], vis3[MAX + 1];
int indegree[MAX + 1];
vector<int> graph[MAX + 1];
int n;

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

int clen(int node, int d) {
  vis3[node] = 1;
  int dst = graph[node][0];
  if (vis3[dst]) return d;
  else return clen(dst, d + 1);
}

void mark(int node, int v) {
  vis2[node] = v;
  int dst = graph[node][0];
  if (!vis2[dst]) mark(dst, v);
}

void plen(int node) {
  vis[node] = 1;
  int dst = graph[node][0];
  if (vis2[dst]) vis[node] += vis2[dst];
  else if (vis[dst]) vis[node] += vis[dst];
  else {
    plen(dst);
    vis[node] += vis[dst];
  }
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 1; i <= n; i++) {
    int nxt = 0;
    for (char c : to_string(i)) nxt = nxt + c - '0';
    nxt = (nxt + i - 1) % n + 1;
    graph[i].push_back(nxt);
    indegree[nxt]++;
  }

  for (int i = 1; i <= n; i++) {
    if (!vis[i]) dfs(i);
  }

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (vis[i] == 2 && !vis2[i]) {
      int v = clen(i, 1);
      ans = max(ans, v);
      mark(i, v);
    }
  }
  memset(vis, 0, sizeof(vis));
  for (int i = 1; i <= n; i++) {
    if (!indegree[i]) {
      plen(i);
      ans = max(ans, vis[i]);
    }
  }

  cout << ans << '\n';
}
