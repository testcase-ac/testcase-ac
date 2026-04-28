#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 30000;
vector<int> adj[MAXN + 1];
int disc[MAXN + 1], C[MAXN + 1], t;

int dfs(int v, int p) {
  disc[v] = ++t;
  int ret = disc[v], child = 0, is_root = (p == -1);

  for (auto& u : adj[v]) {
    if (u == p) continue;
    if (!disc[u]) {
      ++child;
      int low = dfs(u, v);
      if (!is_root && low >= disc[v]) C[v] = 1;
      ret = min(ret, low);
    } else {
      ret = min(ret, disc[u]);
    }
  }
  if (is_root && child > 1) C[v] = 1;

  return ret;
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= N; ++i) {
    adj[i].clear();
    disc[i] = C[i] = 0;
  }

  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  for (int i = 1; i <= N; ++i) {
    if (!disc[i]) dfs(i, -1);
  }

  if (accumulate(C + 1, C + N + 1, 0)) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
