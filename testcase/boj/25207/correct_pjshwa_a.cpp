#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
int a[MAX + 1];
vector<int> graph[MAX + 1];
map<pii, bool> d;

bool o(int u, int v) {
  if (u > v) swap(u, v);
  if (d.count({u, v})) return d[{u, v}];

  if (a[u] != a[v]) return d[{u, v}] = false;
  if (graph[u].size() != graph[v].size()) return d[{u, v}] = false;

  int n = graph[u].size();
  for (int i = 0; i < (n + 1) / 2; i++) {
    if (!o(graph[u][i], graph[v][n - 1 - i])) return d[{u, v}] = false;
  }
  return d[{u, v}] = true;
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
  }
  for (int i = 1; i <= n; i++) sort(graph[i].begin(), graph[i].end());

  vector<int> ans;
  for (int i = 1; i <= n; i++) {
    if (o(i, i)) ans.push_back(i);
  }

  cout << ans.size() << '\n';
  for (int e : ans) cout << e << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
