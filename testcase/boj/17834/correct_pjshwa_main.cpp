#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, BIAS = 50000;
vector<int> graph[MAX + 1];
bool vis[MAX + 1];
ll cnt1, cnt2;

void dfs(int v) {
  vis[v] = 1;
  for (int d : graph[v]) {
    if (!vis[d]) dfs(d);
  }
}

void dfs2(int v, bool f) {
  vis[v] = 1;
  f ? cnt1++ : cnt2++;
  for (int d : graph[v]) {
    if (!vis[d]) dfs2(d, !f);
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v + BIAS);
    graph[v].push_back(u + BIAS);
    graph[u + BIAS].push_back(v);
    graph[v + BIAS].push_back(u);
  }

  dfs(1);
  if (vis[1 + BIAS]) return cout << "0\n", void();
  else {
    memset(vis, 0, sizeof vis);
    dfs2(1, 0);
    cout << 2 * cnt1 * cnt2 << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
