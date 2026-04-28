#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int deg[MAXN + 1], dp[MAXN + 1];
vector<int> adj[MAXN + 1];

int rec(int v, int p) {
  if (dp[v] != -1) return dp[v];
  if (deg[v] == 1) return dp[v] = 1;

  int win = 0;
  for (int u : adj[v]) {
    if (u == p) continue;
    win += rec(u, v);
  }
  return dp[v] = win > 1;
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N - 1; ++i) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v); adj[v].push_back(u);
    ++deg[u]; ++deg[v];
  }

  memset(dp, -1, sizeof(dp));
  cout << rec(1, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
