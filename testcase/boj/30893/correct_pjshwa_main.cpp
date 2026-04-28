#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
vector<int> adj[MAX + 1];
int C[MAX + 1], deg[MAX + 1], from[MAX + 1];

void solve() {
  int N, S, E; cin >> N >> S >> E;
  for (int i = 0; i < N - 1; ++i) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
    ++deg[u]; ++deg[v];
  }

  queue<pii> q;
  q.emplace(S, 1); C[S] = 1;
  while (!q.empty()) {
    auto [v, c] = q.front(); q.pop();
    for (int u : adj[v]) {
      if (C[u]) continue;
      C[u] = 3 - c; from[u] = v;
      q.emplace(u, 3 - c);
    }
  }

  vector<int> path;
  for (int v = from[E]; v != S; v = from[v]) path.push_back(v);
  path.push_back(S);

  for (int v : path) {
    if (C[v] == 2 && deg[v] != 2) return cout << "Second\n", void();
  }
  cout << "First\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
