#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int parent[1001];

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

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) parent[i] = i;
  map<int, vector<int>> emap;

  while (m--) {
    string op;
    int u, v;
    cin >> op >> u >> v;
    if (op == "E") {
      emap[u].push_back(v);
      emap[v].push_back(u);
    }
    else Union(u, v);
  }

  for (auto [u, vv] : emap) {
    int sz = vv.size();
    for (int i = 0; i < sz - 1; i++) Union(vv[i], vv[i + 1]);
  }

  set<int> teams;
  for (int i = 1; i <= n; i++) teams.insert(Find(i));
  cout << teams.size() << '\n';
}
