#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
vector<int> graph[MAX + 1];
int W[MAX + 1];
int d[MAX + 1][MAX + 1];

int r(int v, int p, int f) {
  if (d[v][f] != -1) return d[v][f];

  int cur1 = 0, cur2 = 0;

  // Choose this node
  for (int u : graph[v]) {
    if (u == p) continue;
    cur1 += r(u, v, v);
  }

  // Don't choose this node
  for (int u : graph[v]) {
    if (u == p) continue;
    cur2 += r(u, v, f);
  }

  int ret = min(cur1 + W[v], cur2 + W[v] - W[f]);
  return d[v][f] = ret;
}

void solve() {
  int n, root;
  cin >> n >> root;

  for (int i = 1; i <= n; ++i) cin >> W[i];
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  
  memset(d, -1, sizeof(d));

  int ans = 0;
  for (int v : graph[root]) {
    ans += r(v, root, root);
  }
  cout << ans + W[root] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
