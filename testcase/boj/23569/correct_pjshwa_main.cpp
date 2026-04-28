#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
bool adj[MAXN][MAXN];
int color[MAXN], indegree[MAXN], n;
int cnt, tot;

void dfs(int v, int c) {
  color[v] = c;
  cnt += c; tot += 1;

  for (int u = 0; u < n; ++u) {
    if (!adj[v][u]) continue;

    if (color[u] == -1) dfs(u, c ^ 1);
    else if (color[u] == c) {
      cout << "-1\n";
      exit(0);
    }
  }
}

void solve() {
  int m; cin >> n >> m;

  for (int v = 0; v < n; ++v) for (int u = 0; u < n; ++u) adj[v][u] = true;
  for (int v = 0; v < n; ++v) {
    adj[v][v] = false;
    indegree[v] = n - 1;
  }
  while (m--) {
    int u, v; cin >> u >> v; --u; --v;
    adj[u][v] = adj[v][u] = false;
    --indegree[u]; --indegree[v];
  }

  memset(color, -1, sizeof(color));
  vector<pii> chunks;
  for (int v = 0; v < n; ++v) {
    if (color[v] != -1) continue;
    cnt = tot = 0;
    dfs(v, 0);
    chunks.emplace_back(cnt, tot - cnt);
  }

  int Z = chunks.size();
  vector<vector<bool>> dp(Z + 1, vector<bool>(n + 1));
  dp[0][0] = true;

  for (int i = 1; i <= Z; ++i) {
    auto [c1, c2] = chunks[i - 1];

    // choose one of two values
    for (int j = 0; j <= n; ++j) {
      if (j >= c1 && dp[i - 1][j - c1]) dp[i][j] = true;
      if (j >= c2 && dp[i - 1][j - c2]) dp[i][j] = true;
    }
  }

  int ans = n;
  for (int j = 0; j <= n; ++j) {
    if (dp[Z][j]) ans = min(ans, abs(j - (n - j)));
  }
  cout << ans << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
