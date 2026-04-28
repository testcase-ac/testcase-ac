#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
vector<int> graph[MAX];
ll cur;
int cost[MAX][2];

void dfs(int v, int p, int c) {
  cur += cost[v][c];
  for (int u : graph[v]) {
    if (u == p) continue;
    dfs(u, v, c ^ 1);
  }
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  for (int i = 0; i < n; i++) cin >> cost[i][0] >> cost[i][1];

  cur = 0;
  dfs(0, -1, 0);
  ll ans = cur;
  cur = 0;
  dfs(0, -1, 1);
  ans = min(ans, cur);

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
