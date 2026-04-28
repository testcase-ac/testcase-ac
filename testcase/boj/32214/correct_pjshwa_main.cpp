#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
vector<int> adj[MAXN + 1], U[5];
vector<pii> res;

void dfs(int v, int p, int l) {
  if (l > 1) U[l % 5].push_back(v);
  for (int u : adj[v]) {
    if (u == p) continue;
    dfs(u, v, l + 1);
  }
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N - 1; ++i) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v); adj[v].push_back(u);
  }
  dfs(1, 0, 0);

  for (int l = 0; l < 5; ++l) {
    int Z = U[l].size();
    if (Z > N / 5) continue;

    cout << Z << '\n';
    for (int v : U[l]) cout << "1 " << v << '\n';
    return;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
