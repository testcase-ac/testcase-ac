#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
vector<pii> graph[MAX + 1];
int mdist[MAX + 1][MAX + 1];
bool part[MAX + 1][MAX + 1];
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

void dfs(int v, int p, int s, int d) {
  mdist[s][v] = d;

  for (auto [u, w] : graph[v]) {
    if (u == p || !part[u][v]) continue;
    dfs(u, v, s, max(d, w));
  }
}

void solve() {
  int n, m, q;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) parent[i] = i;

  vector<tuple<int, int, int>> ta;
  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back({v, w});
    graph[v].push_back({u, w});
    ta.push_back({w, u, v});
  }
  sort(ta.begin(), ta.end());

  ll mst_val = 0;
  for (auto [w, x, y] : ta) {
    if (Find(x) == Find(y)) continue;
    mst_val += w;
    part[x][y] = part[y][x] = true;
    Union(x, y);
  }

  for (int i = 1; i <= n; i++) dfs(i, -1, i, 0);

  cin >> q;
  while (q--) {
    int u, v;
    cin >> u >> v;
    cout << mst_val - mdist[u][v] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
