#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
vector<int> graph[MAXN + 1];
int C[MAXN + 1];
bool vis[MAXN + 1];

bool dfs(int v) {
  for (int u : graph[v]) {
    if (vis[u]) continue;
    vis[u] = true;
    if (C[u] == -1 || dfs(C[u])) {
      C[u] = v;
      return true;
    }
  }
  return false;
}

void solve() {
  int N, M, K; cin >> N >> M >> K;
  for (int i = 1; i <= N; ++i) {
    int k, x; cin >> k;
    while (k--) cin >> x, graph[i].push_back(x);
  }

  int match = 0;
  fill(C, C + M + 1, -1);

  for (int i = 1; i <= N; ++i) {
    fill(vis, vis + M + 1, false);
    if (dfs(i)) match++;
  }

  for (int i = 1; i <= N; ++i) {
    if (K == 0) break;
    fill(vis, vis + M + 1, false);
    if (dfs(i)) match++, K--;
  }

  cout << match << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
