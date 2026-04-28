#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
vector<pii> graph[MAX + 1];
ll ans;

void dfs(int v, int p, int c) {
  ll s = c, x = c;
  for (auto [u, w] : graph[v]) {
    if (u == p) continue;
    s += w, x = max(x, (ll)w);
  }

  ll used;
  if (s > 2 * x) used = (s + 1) / 2;
  else used = x;
  ans += used - c;

  for (auto [u, w] : graph[v]) {
    if (u == p) continue;
    dfs(u, v, w);
  }
}

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back({v, w});
    graph[v].push_back({u, w});
  }

  ans = 0;
  dfs(0, -1, 0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
