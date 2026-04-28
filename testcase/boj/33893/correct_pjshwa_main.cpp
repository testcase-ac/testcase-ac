#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 16;
vector<int> adj[MAXN];

// where should defense i go, if player is at j
int W[MAXN][MAXN];
int cdist[MAXN], vdist[MAXN][1 << MAXN];

void solve() {
  int N, M, K; cin >> N >> M >> K;
  while (M--) {
    int u, v; cin >> u >> v; --u; --v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  for (int i = 0; i < N; ++i) adj[i].push_back(i);

  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    if (i == j) {
      W[i][j] = i;
      continue;
    }

    memset(cdist, 0x3f, sizeof(cdist));
    queue<int> q;
    cdist[j] = 0; q.push(j);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int v : adj[u]) {
        if (cdist[v] > cdist[u] + 1) {
          cdist[v] = cdist[u] + 1;
          q.push(v);
        }
      }
    }

    int k = N;
    for (int v : adj[i]) {
      if (cdist[v] == cdist[i] - 1) k = min(k, v);
    }
    assert(k < N);
    W[i][j] = k;
  }

  int dmask = 0, d;
  while (K--) {
    cin >> d; --d;
    dmask |= (1 << d);
  }

  vector<vector<int>> color(N, vector<int>(1 << N, 0));
  function<bool(int, int)> dfs_cycle = [&](int u, int mask) {
    color[u][mask] = 1;
    for (int v : adj[u]) {
      if (mask & (1 << u)) break;
      if (mask & (1 << v)) continue;
      int nmask = 0;
      for (int i = 0; i < N; ++i) {
        if (!(mask & (1 << i))) continue;
        nmask |= (1 << W[i][v]);
      }
      if (color[v][nmask] == 1) return true;
      if (color[v][nmask] == 0 && dfs_cycle(v, nmask)) return true;
    }
    color[u][mask] = 2;
    return false;
  };
  if (dfs_cycle(0, dmask)) {
    cout << "DaeHeungMin\n";
    return;
  }

  queue<pii> q;
  memset(vdist, 0x3f, sizeof(vdist));
  q.push({0, dmask}); vdist[0][dmask] = 0;

  int ans = 0;
  while (!q.empty()) {
    auto [u, mask] = q.front(); q.pop();
    if (vdist[u][mask] > ans) ans = vdist[u][mask];
    if (mask & (1 << u)) continue;

    for (int v : adj[u]) {
      if (mask & (1 << v)) continue;
      int nmask = 0;
      for (int i = 0; i < N; ++i) {
        if (!(mask & (1 << i))) continue;
        nmask |= (1 << W[i][v]);
      }
      if (vdist[v][nmask] > vdist[u][mask] + 1) {
        vdist[v][nmask] = vdist[u][mask] + 1;
        q.push({v, nmask});
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
