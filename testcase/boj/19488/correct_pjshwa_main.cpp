#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
vector<int> adj[MAXN + 1];
int parent[MAXN + 1], usz[MAXN + 1];
bool ban[MAXN + 1];
int deg[MAXN + 1];

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
  int N, M, D; cin >> N >> M >> D;

  for (int j = 0; j < M; ++j) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
    ++deg[u]; ++deg[v];
  }

  priority_queue<pii, vector<pii>, greater<pii>> pq;
  for (int i = 1; i <= N; ++i) pq.emplace(deg[i], i);

  while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (ban[u]) continue;
    if (d >= D) break;

    ban[u] = true; deg[u] = 0;
    for (int v : adj[u]) {
      if (ban[v]) continue;
      pq.emplace(--deg[v], v);
    }
  }

  iota(parent, parent + N + 1, 0);
  fill(usz, usz + N + 1, 1);
  for (int u = 1; u <= N; ++u) {
    if (ban[u]) continue;
    for (int v : adj[u]) {
      if (!ban[v]) Union(u, v);
    }
  }

  int max_gs = 0, max_gi;
  for (int i = 1; i <= N; ++i) {
    if (ban[i]) continue;
    int gi = Find(i);
    int gs = usz[gi];
    if (gs > max_gs) {
      max_gs = gs;
      max_gi = gi;
    }
  }
  if (max_gs == 0) return cout << "NIE\n", void();

  cout << max_gs << '\n';
  for (int i = 1; i <= N; ++i) {
    if (ban[i] || Find(i) != max_gi) continue;
    cout << i << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
