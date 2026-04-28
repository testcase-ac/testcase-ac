#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
vector<int> adj[MAX + 1];
int ans, d;

void dfs(int v) {
  int z = adj[v].size();
  if (z > d) ans += (z - 2) / (d - 1);
  for (int u : adj[v]) dfs(u);
}

void solve() {
  int n; cin >> n >> d;
  for (int i = 1; i <= n; i++) {
    int x; cin >> x;
    adj[x].push_back(i);
  }
  dfs(0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
