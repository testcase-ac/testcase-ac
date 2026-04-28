#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int vis[2 * MAX + 1];
vector<int> graph[2 * MAX + 1];

void dfs(int v, int t) {
  vis[v] = t;
  for (int d : graph[v]) {
    if (!vis[d]) dfs(d, t);
  }
}

void solve() {
  int n, m, q;
  cin >> n >> m >> q;
  while (m--) {
    int o, a, b;
    cin >> o >> a >> b;
    if (o == 0) {
      graph[a].push_back(b);
      graph[b].push_back(a);
      graph[a + MAX].push_back(b + MAX);
      graph[b + MAX].push_back(a + MAX);
    }
    if (o == 1) {
      graph[a].push_back(b + MAX);
      graph[a + MAX].push_back(b);
      graph[b].push_back(a + MAX);
      graph[b + MAX].push_back(a);
    }
  }

  int cc = 0;
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      dfs(i, 2 * cc + 2);
      if (!vis[i + MAX]) dfs(i + MAX, 2 * cc + 3);
      cc++;
    }
  }

  while (q--) {
    int a, b;
    cin >> a >> b;

    if (vis[a] / 2 != vis[b] / 2) cout << "Unknown\n";
    else if (vis[a] == vis[a + MAX]) cout << "Error\n";
    else if (vis[a] == vis[b]) cout << "Friend\n";
    else cout << "Enemy\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
