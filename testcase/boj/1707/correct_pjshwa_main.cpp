#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<int> graph[20001];
int vis[20001];

void bfs(int sv) {
  // Vertex, depth
  queue<pii> q;
  q.push({sv, 0});

  int vtx, dpt;
  while (!q.empty()) {
    tie(vtx, dpt) = q.front();
    q.pop();

    if (vis[vtx]) continue;
    vis[vtx] = (dpt % 2) + 1;

    for (auto dst : graph[vtx]) {
      if (!vis[dst]) q.push({dst, dpt + 1});
    }
  }
}

int main() {
  fast_io();

  int t, v, e, v1, v2;
  cin >> t;
  while (t--) {
    cin >> v >> e;

    for (int i = 1; i <= v; i++) graph[i].clear();
    memset(vis, 0, sizeof(vis));

    for (int i = 0; i < e; i++) {
      cin >> v1 >> v2;
      graph[v1].push_back(v2);
      graph[v2].push_back(v1);
    }

    for (int i = 1; i <= v; i++) {
      if (!vis[i]) bfs(i);
    }

    bool is_bipartite = true;
    for (int src_vtx = 1; src_vtx <= v; src_vtx++) {
      for (auto dst_vtx : graph[src_vtx]) {
        if (vis[src_vtx] == vis[dst_vtx]) is_bipartite = false;
      }
    }

    cout << (is_bipartite ? "YES" : "NO") << '\n';
  }
}
