#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
vector<int> graph[MAX + 1];
int a[MAX + 1], par[MAX + 1];
ll d[MAX + 1][2];

ll dfs(int v, int u) {
  if (d[v][u] != -1) return d[v][u];

  ll res = 0;
  for (int d : graph[v]) res += dfs(d, 0);

  ll smax = 0;
  if (u == 0) {
    for (int d : graph[v]) smax = max(smax, dfs(d, 1) - dfs(d, 0));
  }

  res += smax;
  return d[v][u] = res + u * a[v] * a[par[v]];
}

void solve() {
  int n;
  cin >> n;
  for (int i = 2; i <= n; i++) {
    cin >> par[i];
    graph[par[i]].push_back(i);
  }
  for (int i = 1; i <= n; i++) cin >> a[i];

  memset(d, -1, sizeof d);
  cout << dfs(1, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
