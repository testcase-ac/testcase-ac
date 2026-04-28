#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3e5;
vector<pii> adj[MAXN + 1];
int N, M, K, C[MAXN + 1];
bool f;

void dfs(int v, int c) {
  C[v] = c;
  for (auto [u, p] : adj[v]) {
    // keep color
    if (p == 0) {
      if (C[u] == -1) dfs(u, c);
      else if (C[u] != c) f = true;
    }
    // change color
    else {
      if (C[u] == -1) dfs(u, 3 - c);
      else if (C[u] == c) f = true;
    }
  }
}

void solve_Kodd() {
  while (M--) {
    int u, v, w; cin >> u >> v >> w;
    if (w % K) return cout << "No\n", void();
  }
  cout << "Yes\n";
}

void solve_Keven() {
  while (M--) {
    int u, v, w; cin >> u >> v >> w;
    if (w % (K / 2)) return cout << "No\n", void();

    int p = !(w % K == 0);
    adj[u].emplace_back(v, p);
    adj[v].emplace_back(u, p);
  }

  // graph should be bipartite
  memset(C, -1, sizeof(C)); f = false;
  for (int i = 1; i <= N; ++i) {
    if (C[i] == -1) dfs(i, 1);
    if (f) return cout << "No\n", void();
  }
  cout << "Yes\n";
}

void solve() {
  cin >> N >> M >> K;
  if (K % 2 == 1) solve_Kodd();
  else solve_Keven();
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
