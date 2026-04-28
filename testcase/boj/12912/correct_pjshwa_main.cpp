#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pil = pair<int, ll>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000;
vector<tii> graph[MAX];
bool vis[MAX], ban[MAX];
int parent[MAX];

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

pil maxd(int node, ll cd) {
  vis[node] = true;

  ll mv = node, md = cd;
  for (tii dst : graph[node]) {
    auto [v, i, d] = dst;
    if (ban[i]) continue;

    if (!vis[v]) {
      auto [dv, dd] = maxd(v, cd + d);
      if (md < dd) md = dd, mv = dv;
    }
  }

  return {mv, md};
}

void solve() {
  int n;
  cin >> n;

  vector<tii> edges;
  for (int i = 0; i < n - 1; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    graph[a].push_back({b, i, w});
    graph[b].push_back({a, i, w});
    edges.push_back({a, b, w});
  }

  ll ans = 0;
  for (int i = 0; i < n - 1; i++) {
    ban[i] = true;

    for (int j = 0; j < n; j++) parent[j] = j;
    for (int j = 0; j < n - 1; j++) {
      if (i == j) continue;
      auto [a, b, w] = edges[j];
      Union(a, b);
    }

    map<int, int> f;
    for (int j = 0; j < n; j++) f[Find(j)] = j;

    int vs[2];
    int x = 0;
    memset(vis, 0, sizeof(vis));
    for (auto [_, v] : f) {
      vs[x] = maxd(v, 0).first;
      x ^= 1;
    }
    memset(vis, 0, sizeof(vis));
    ll cur = 0;
    for (auto [_, v] : f) {
      cur += maxd(vs[x], 0).second;
      x ^= 1;
    }

    ans = max(ans, cur + get<2>(edges[i]));
    ban[i] = false;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
