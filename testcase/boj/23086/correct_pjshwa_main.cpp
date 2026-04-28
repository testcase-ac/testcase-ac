#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
int vis[MAX + 1];

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

  int n, m, k, x;
  cin >> n >> m >> k;

  vector<pii> edges(m);
  stack<pii> restore;

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    edges[i] = {u, v};
  }
  for (int i = 0; i < k; i++) {
    cin >> x;
    restore.push(edges[x - 1]);
    edges[x - 1] = {-1, -1};
  }
  for (int i = 0; i < m; i++) {
    auto [u, v] = edges[i];
    if (u == -1) continue;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  bfs(1);
  bool is_bipartite = true;
  for (int src_vtx = 1; src_vtx <= n; src_vtx++) {
    for (auto dst_vtx : graph[src_vtx]) {
      if (vis[src_vtx] == vis[dst_vtx]) is_bipartite = false;
    }
  }

  if (!is_bipartite) return cout << "-1\n", 0;
  while (!restore.empty()) {
    auto [u, v] = restore.top();
    if (vis[u] == vis[v]) break;
    restore.pop();
  }

  cout << restore.size() << "\n";

  int group1_cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (vis[i] == 1) group1_cnt++;
  }
  int group2_cnt = n - group1_cnt;

  if (group1_cnt > group2_cnt) swap(group1_cnt, group2_cnt);
  cout << group1_cnt << " " << group2_cnt << "\n";
}
