#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
int parent[MAX + 1], usz[MAX + 1];

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

  parent[y] = x;
  usz[x] += usz[y];
}

void solve() {
  int N, M; cin >> N >> M;
  iota(parent, parent + N + 1, 0);
  fill(usz, usz + N + 1, 1);

  vector<pii> edges;
  for (int i = 0; i < M; ++i) {
    int u, v; cin >> u >> v;
    edges.push_back({u, v});
  }

  int X; cin >> X;
  for (auto& edge : edges) {
    int u = edge.first, v = edge.second;
    if (u == X || v == X) continue;
    Union(u, v);
  }

  set<int> groups;
  for (int i = 1; i <= N; ++i) {
    if (i == X) continue;
    groups.insert(Find(i));
  }

  map<int, int> deg;
  for (auto& edge : edges) {
    int u = edge.first, v = edge.second;
    if (u == X) {
      int g = Find(v);
      deg[g]++;
    }
    else if (v == X) {
      int g = Find(u);
      deg[g]++;
    }
  }

  int ans = 1;
  for (int g : groups) {
    ans = max(ans, usz[g] + (deg[g] == 1));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
