#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
vector<int> adj[MAXN + 1];
int disc[MAXN + 1], t;
int parent[MAXN + 1], usz[MAXN + 1];
vector<pii> d_edges;

int dfs(int v, int p) {
  disc[v] = ++t;
  int ret = disc[v];

  for (auto& u : adj[v]) {
    if (u == p) continue;
    if (!disc[u]) {
      int low = dfs(u, v);
      if (low > disc[v]) {
        d_edges.emplace_back(min(u, v), max(u, v));
      }
      ret = min(ret, low);
    } else {
      ret = min(ret, disc[u]);
    }
  }

  return ret;
}

int Find(int x) {
  if (parent[x] == x) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x == y) return;

  parent[y] = x;
  usz[x] += usz[y];
}

void solve() {
  int N, M, K; cin >> N >> M >> K;
  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  for (int i = 1; i <= N; ++i) {
    if (!disc[i]) dfs(i, -1);
  }

  iota(parent, parent + N + 1, 0);
  fill(usz, usz + N + 1, 1);
  for (auto& [u, v] : d_edges) Union(u, v);

  map<int, int> by_g, by_s;
  for (int i = 1; i <= N; ++i) ++by_g[Find(i)];
  while (K--) {
    int x; cin >> x;
    ++by_s[Find(x)];
  }

  int ans = 0;
  for (auto& [k, v] : by_g) {
    if (!by_s[k]) continue;
    ans ^= (v - by_s[k]);
  }
  ans = ans == 0;
  int c; cin >> c;
  ans ^= c;

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
