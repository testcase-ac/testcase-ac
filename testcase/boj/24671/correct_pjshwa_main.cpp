#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
vector<int> adj[MAX + 1];
int U[MAX + 1], deg[MAX + 1], ans;

void dfs(int v, int p) {
  int leaf = 1;
  for (int u : adj[v]) {
    if (u == p) continue;
    leaf = 0;
    dfs(u, v);
    U[v] += U[u];
  }
  if (leaf) U[v] = 1;

  if (U[v] > 1) {
    ans++;
    U[v] = 0;
  }
}

void solve() {
  int n; cin >> n;
  for (int i = 2; i <= n; i++) {
    int p; cin >> p;
    adj[p].push_back(i);
    adj[i].push_back(p);
    deg[p]++; deg[i]++;
  }

  for (int i = 1; i <= n; i++) {
    if (deg[i] < 2) continue;
    dfs(i, 0); break;
  }

  if (ans == 0) ans = 1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
