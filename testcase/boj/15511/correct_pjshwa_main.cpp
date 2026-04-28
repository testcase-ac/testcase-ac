#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
vector<int> graph[MAX + 1];
int parent[MAX + 1];

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

void add_edge(int x, int y) {
  graph[x].push_back(y);
  graph[y].push_back(x);
}

int main() {
  fast_io();

  int n, m, u, v;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) parent[i] = i;
  while (m--) {
    cin >> u >> v;
    add_edge(u, v);
  }

  for (int i = 1; i <= n; i++) {
    int sz = graph[i].size();
    if (sz <= 1) continue;

    for (int j = 0; j < sz - 1; j++) {
      if (Find(i) == Find(graph[i][j]) || Find(i) == Find(graph[i][j + 1])) {
        cout << "IMPOSSIBLE";
        return 0;
      }
      Union(graph[i][j], graph[i][j + 1]);
    }
  }
  cout << "POSSIBLE";
}
