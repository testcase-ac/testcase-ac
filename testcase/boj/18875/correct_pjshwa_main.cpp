#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
vector<int> adj[MAX + 1];
int parent[MAX + 1];
set<int> E[MAX + 1];

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

  if (x == y) return;

  if (E[x].size() < E[y].size()) swap(x, y);
  for (int e : E[y]) {
    E[x].insert(e);
    parent[e] = x;
  }
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= N; i++) {
    parent[i] = i;
    E[i].insert(i);
  }
  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
