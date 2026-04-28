#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 36;
int G[MAXN + 1];
vector<int> adj[MAXN + 1];

int n, m;
void solve() {
  for (int i = 1; i <= n; ++i) adj[i].clear();

  for (int i = 3; i <= n; ++i) cin >> G[i];
  for (int j = 0; j < m; ++j) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v); adj[v].push_back(u);
  }
}

int main() {
  fast_io();

  while (cin >> n >> m) {
    if (n == 0 && m == 0) break;
    solve();
  }
}
