#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e4;
vector<pii> adj[MAXN + 1];
int dp[MAXN + 1], ans;

void dfs1(int v) {
  for (auto [u, w] : adj[v]) {
    dfs1(u);
    dp[v] = max(dp[v], dp[u] + w);
  }
}

void dfs2(int v, int limit) {
  for (auto [u, w] : adj[v]) {
    if (dp[u] + w >= limit) {
      int dif = min(dp[u] + w - limit, w);
      ans += dif;
      dfs2(u, limit - (w - dif));
    }
  }
}

void solve() {
  int N, H; cin >> N >> H;

  int root;
  for (int i = 1; i <= N; ++i) {
    int p, w; cin >> p >> w;
    if (p == 0 && w == 0) root = i;
    else adj[p].emplace_back(i, w);
  }

  dfs1(root);
  dfs2(root, H);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
