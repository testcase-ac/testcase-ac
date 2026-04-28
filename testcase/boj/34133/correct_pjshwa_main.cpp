#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
vector<int> adj[MAXN + 1];
int indegree[MAXN + 1], L[MAXN + 1], vis[MAXN + 1], v;

int dfs(int v) {
  if (L[v] != -1) return L[v];
  int ret = 1;
  for (int u : adj[v]) ret = max(ret, dfs(u) + 1);
  return L[v] = ret;
}

void solve() {
  int N, M; cin >> N >> M;
  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    ++indegree[v];
  }
  memset(L, -1, sizeof(L));
  for (int i = 1; i <= N; ++i) {
    if (indegree[i] == 0) dfs(i);
  }
  cout << *max_element(L + 1, L + N + 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
