#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, INF = 0x3f3f3f3f;
vector<pii> adj[MAXN + 1];
int cdist[MAXN + 1], dp[MAXN + 1][2];
int S, F;

int dfs(int v, int t) {
  if (dp[v][t] != -1) return dp[v][t];
  if (v == F) return dp[v][t] = 1;

  int ret = 0;
  for (auto& [u, l] : adj[v]) {
    if (cdist[v] + l == cdist[u]) {
      ret += dfs(u, t);
    }
    if (t == 0 && cdist[v] + l == cdist[u] + 1) {
      ret += dfs(u, 1);
    }
  }
  return dp[v][t] = ret;
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= N; ++i) adj[i].clear();
  while (M--) {
    int u, v, l; cin >> u >> v >> l;
    adj[u].emplace_back(v, l);
  }
  cin >> S >> F;

  memset(cdist, 0x3f, sizeof(cdist));
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.emplace(0, S); cdist[S] = 0;

  while (!pq.empty()) {
    auto [cd, cv] = pq.top(); pq.pop();
    if (cd > cdist[cv]) continue;
    for (auto [nv, nl] : adj[cv]) {
      int nd = cd + nl;
      if (nd < cdist[nv]) {
        cdist[nv] = nd;
        pq.emplace(nd, nv);
      }
    }
  }

  int min_dist = cdist[F];
  assert(min_dist != INF);

  memset(dp, -1, sizeof(dp));
  cout << dfs(S, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
