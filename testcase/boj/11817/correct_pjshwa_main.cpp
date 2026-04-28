#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5, INF = 0x3f3f3f3f;
vector<pii> adj[MAXN + 1];
int cdistA[MAXN + 1], cdistB[MAXN + 1];

vector<pii> res;
int disc[MAXN + 1], t;

int dfs(int v, int p) {
  disc[v] = ++t;
  int low = disc[v];

  for (auto& [u, _] : adj[v]) {
    if (u == p) continue;
    if (!disc[u]) {
      int ret = dfs(u, v);
      if (ret > disc[v]) {
        res.emplace_back(min(v, u), max(v, u));
      }
      low = min(low, ret);
    } else {
      low = min(low, disc[u]);
    }
  }

  return low;
}

void dijk(int s, int cdist[]) {
  fill(cdist, cdist + MAXN + 1, INF);
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.emplace(0, s); cdist[s] = 0;
  
  while (!pq.empty()) {
    auto [d, v] = pq.top(); pq.pop();
    if (cdist[v] < d) continue;
    for (auto& [u, w] : adj[v]) {
      if (cdist[u] > cdist[v] + w) {
        cdist[u] = cdist[v] + w;
        pq.emplace(cdist[u], u);
      }
    }
  }
}

void solve() {
  int N, M; cin >> N >> M;
  while (M--) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }
  dfs(1, 0);

  int A, B; cin >> A >> B;
  dijk(A, cdistA);
  dijk(B, cdistB);

  int ans = INF;
  for (auto& [u, v] : res) {
    ans = min(ans, max(cdistA[u], cdistB[v]));
    ans = min(ans, max(cdistA[v], cdistB[u]));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
