#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3e5;
set<int> adj[MAX + 1];
int C[MAX + 1];

void solve() {
  int n, m, k; cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) cin >> C[i];
  while (m--) {
    int u, v; cin >> u >> v;
    adj[u].insert(C[v]);
    adj[v].insert(C[u]);
  }

  for (int i = 1; i <= n; i++) {
    if (adj[i].size() + 1 < k) return cout << "1\n", void();
  }
  cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
