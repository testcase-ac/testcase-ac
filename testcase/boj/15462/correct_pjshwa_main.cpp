#include <bits/stdc++.h>
using namespace std;

vector<int> graph[(int)1e5 + 1];

// 0: Not visited
// 1: Visited
// 2: Part of cycle
int vis[(int)1e5 + 1];

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
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

int main() {
  fast_io();

  int n, s, cnt;

  cin >> n;
  cnt = 0;

  for (int i = 1; i <= n; i++) {
    cin >> s;
    graph[i].push_back(s);
  }

  for (int i = 1; i <= n; i++) {
    if (!vis[i]) dfs(i);
  }

  for (int i = 1; i <= n; i++) {
    if (vis[i] != 1) cnt++;
  }
  cout << cnt << '\n';
}
