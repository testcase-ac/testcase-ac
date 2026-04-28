#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 1000;
vector<int> adj[MAX + 1];
bool vis[MAX + 1];
int N;

void init() {
  for (int i = 1; i <= N; i++) vis[i] = false;
}

void dfs(int v) {
  vis[v] = true;
  cout << v << ' ';
  for (int u : adj[v]) {
    if (vis[u]) continue;
    dfs(u);
  }
}

void bfs(int v) {
  queue<int> q;
  q.push(v); vis[v] = true;
  while (!q.empty()) {
    int v = q.front(); q.pop();
    cout << v << ' ';

    for (int u : adj[v]) {
      if (vis[u]) continue;
      q.push(u); vis[u] = true;
    }
  }
}

int main() {
  int M, V; cin >> N >> M >> V;
  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v); adj[v].push_back(u);
  }
  for (int i = 1; i <= N; i++) {
    sort(adj[i].begin(), adj[i].end());
  }

  init(); dfs(V); cout << '\n';
  init(); bfs(V); cout << '\n';
}
