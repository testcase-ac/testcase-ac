#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
vector<int> adj[MAX + 1];

int A[MAX + 1], S[MAX + 1], R[MAX + 1];
queue<pair<int, int>> Q_by_node[MAX + 1];

void dfs1(int v, int p) {
  S[v] = A[v];
  for (int u : adj[v]) {
    if (u == p) continue;
    dfs1(u, v);
    S[v] += S[u];
  }
}

void dfs2(int v, int p) {
  while (!Q_by_node[v].empty()) {
    auto [i, x] = Q_by_node[v].front(); Q_by_node[v].pop();
    R[i] = S[x];
  }

  for (int u : adj[v]) {
    if (u == p) continue;

    int subs = S[u];
    S[u] = S[v];
    S[v] -= subs;
    dfs2(u, v);
    S[v] += subs;
    S[u] = subs;
  }
}

void solve() {
  int N, Q; cin >> N >> Q;
  for (int i = 1; i <= N; i++) cin >> A[i];

  for (int i = 0; i < N - 1; i++) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs1(1, 0);

  for (int i = 1; i <= Q; i++) {
    int r, v; cin >> r >> v;
    Q_by_node[r].emplace(i, v);
  }
  dfs2(1, 0);

  for (int i = 1; i <= Q; i++) cout << R[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
