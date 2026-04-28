#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50000, INF = 1e9 + 7;
vector<int> graph[MAX + 1];
int n, d[MAX + 1], ssz[MAX + 1];

void dfs1(int v, int p) {
  ssz[v] = 1;
  for (int u : graph[v]) {
    if (u == p) continue;
    dfs1(u, v);
    ssz[v] += ssz[u];
  }
}

void dfs2(int v, int p, int s) {
  int res = s;
  for (int u : graph[v]) {
    if (u == p) continue;
    dfs2(u, v, s + ssz[v] - ssz[u]);
    res = max(res, ssz[u]);
  }
  d[v] = res;
}

void solve() {
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  dfs1(1, -1);
  dfs2(1, -1, 0);

  int mval = *min_element(d + 1, d + n + 1);
  for (int i = 1; i <= n; i++) if (d[i] == mval) cout << i << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
