#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5, MOD = 1e9 + 7;
vector<int> graph[MAX + 1];
bool vis[MAX + 1];
int cnt;

void dfs(int v) {
  vis[v] = 1;
  cnt++;
  for (int d : graph[v]) {
    if (!vis[d]) dfs(d);
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  while (m--) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  ll ans = 1;
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      cnt = 0;
      dfs(i);
      ans = (ans * cnt) % MOD;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
