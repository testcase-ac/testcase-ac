#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX + 1], t[MAX + 1], parent[MAX + 1][21];
bool vis[MAX + 1];
vector<pii> graph[MAX + 1];

void dfs(int v, int sum) {
  t[v] = sum;
  vis[v] = true;
  for (auto [d, w] : graph[v]) {
    if (!vis[d]) {
      parent[d][0] = v;
      dfs(d, sum + w);
    }
  }
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back({v, w});
    graph[v].push_back({u, w});
  }

  dfs(1, 0);
  for (int j = 1; j <= 20; j++) for (int i = 1; i <= n; i++) parent[i][j] = parent[parent[i][j - 1]][j - 1];

  for (int v = 1; v <= n; v++) {
    int x = v, e = a[v];
    for (int i = 19; i >= 0; i--) {
      if (parent[x][i] && t[x] - t[parent[x][i]] <= e) {
        e -= t[x] - t[parent[x][i]];
        x = parent[x][i];
      }
    }
    cout << x << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
