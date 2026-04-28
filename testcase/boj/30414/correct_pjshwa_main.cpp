#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
vector<int> adj[MAX + 1];
int A[MAX + 1], B[MAX + 1];

int dfs(int v, int p) {
  int ret = B[v] - A[v];
  for (int u : adj[v]) {
    if (u == p) continue;
    ret += dfs(u, v);
  }
  return max(ret, 0);
}

void solve() {
  int N, P; cin >> N >> P;
  for (int i = 1; i <= N; ++i) cin >> A[i];
  for (int i = 1; i <= N; ++i) cin >> B[i];
  for (int i = 0; i < N - 1; ++i) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  cout << dfs(P, -1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
