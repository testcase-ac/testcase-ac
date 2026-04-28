#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
vector<int> graph[MAX + 1];
int parent[MAX + 1], ginv[MAX + 1];
bool vis[MAX + 1], is_cycle[MAX + 1], vis2[MAX + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

void dfs(int v, int par) {
  vis[v] = 1;
  for (int d : graph[v]) {
    if (!vis[d]) ginv[d] = v, dfs(d, v);
    else if (par != d && !is_cycle[d]) {
      // Cycle is detected
      for (int x = v; x != d; x = ginv[x]) is_cycle[x] = 1;
      is_cycle[d] = 1;
    }
  }
}

void udfs(int v) {
  vis2[v] = 1;
  for (int d : graph[v]) {
    if (!vis2[d] && !is_cycle[d]) Union(v, d), udfs(d);
  }
}

int main() {
  fast_io();

  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
    parent[i] = i;
  }
  dfs(1, -1);

  for (int i = 1; i <= n; i++) {
    if (is_cycle[i]) udfs(i);
  }

  while (q--) {
    int a, b;
    cin >> a >> b;
    if (Find(a) == Find(b)) cout << "1\n";
    else cout << "2\n";
  }
}
