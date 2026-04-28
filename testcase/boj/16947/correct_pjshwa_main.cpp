#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e3;
int dist[MAX + 1], indegree[MAX + 1];
bool vis[MAX + 1], is_cycle[MAX + 1];
vector<int> graph[MAX + 1];

int find_cycle(int v, int par) {
  vis[v] = true;
  bool cycle_found = false;
  int cycle_base = -1;

  for (int d : graph[v]) {
    if (d == par) continue;
    if (vis[d]) cycle_base = d, cycle_found = true;
    else {
      int res = find_cycle(d, v);
      if (res != -1) cycle_base = res, cycle_found = true;
    }
  }
  vis[v] = false;

  if (cycle_found) {
    is_cycle[v] = true;
    return cycle_base == v ? -1 : cycle_base;
  }
  else return -1;
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
    indegree[a]++;
    indegree[b]++;
  }

  for (int i = 1; i <= n; i++) {
    if (indegree[i] == 1) {
      find_cycle(i, -1);
      break;
    }
  }

  queue<pair<int, int>> q;
  for (int i = 1; i <= n; i++) {
    if (!is_cycle[i]) continue;
    for (int d : graph[i]) if (!is_cycle[d]) q.push({d, 1});
  }

  while (!q.empty()) {
    auto [v, ds] = q.front();
    q.pop();

    if (vis[v]) continue;
    vis[v] = true;
    dist[v] = ds;

    for (int d : graph[v]) if (!vis[d] && !is_cycle[d]) q.push({d, ds + 1}); 
  }

  for (int i = 1; i <= n; i++) cout << dist[i] << ' ';
}
