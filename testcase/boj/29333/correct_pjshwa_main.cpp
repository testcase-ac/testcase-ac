#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
vector<int> adj[MAX + 1];
int from[MAX + 1], vis[MAX + 1];

void solve() {
  int N, M, S, E; cin >> N >> M >> S >> E;

  vector<pii> edges;
  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
    edges.emplace_back(u, v);
  }

  queue<int> q;
  q.push(S); vis[S] = 1;
  while (!q.empty()) {
    int v = q.front(); q.pop();
    for (int u : adj[v]) {
      if (!vis[u]) {
        vis[u] = 1;
        from[u] = v;
        q.push(u);
      }
    }
  }
  if (!vis[E]) return cout << "-1\n", void();

  set<pii> pedg; set<int> pvtx;
  int v = E; pvtx.insert(v);
  do {
    pedg.emplace(from[v], v);
    v = from[v]; pvtx.insert(v);
  } while (v != S);

  for (auto [u, v] : edges) {
    if (pedg.count({u, v})) cout << "0 ";
    else if (pedg.count({v, u})) cout << "1 ";
    else if (pvtx.count(u)) cout << "1 ";
    else if (pvtx.count(v)) cout << "0 ";
    else cout << "0 ";
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
