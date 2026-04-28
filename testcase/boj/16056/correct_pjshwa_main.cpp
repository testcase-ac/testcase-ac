#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1515;
vector<int> adj[MAXN + 1];
int ma[MAXN + 1], mb[MAXN + 1], oma[MAXN + 1], omb[MAXN + 1];
bool vis[MAXN + 1];

bool dfs(int a) {
  vis[a] = true;
  for (int b : adj[a]) {
    if (mb[b] == -1 || (!vis[mb[b]] && dfs(mb[b]))) {
      ma[a] = b; mb[b] = a;
      return true;
    }
  }
  return false;
}

void solve() {
  int N, M, K; cin >> N >> M >> K;
  while (K--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
  }

  int omatch = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 1; i <= N; ++i) {
    if (ma[i] != -1) continue;
    fill(vis, vis + N + 1, false);
    if (dfs(i)) ++omatch;
  }
  memcpy(oma, ma, sizeof ma);
  memcpy(omb, mb, sizeof mb);

  int ans = 0;
  for (int i = 1; i <= N; ++i) {
    memcpy(ma, oma, sizeof ma);
    memcpy(mb, omb, sizeof mb);

    int match = omatch;
    for (int j = N + 1; j <= N + 2; ++j) adj[j] = adj[i];
    for (int j = N + 1; j <= N + 2; ++j) {
      fill(vis, vis + N + 3, false);
      if (dfs(j)) ++match;
    }
    ans = max(ans, match);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
