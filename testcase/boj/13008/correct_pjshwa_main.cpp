#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50, MAXC = 1000;
vector<pii> adj[MAXN];
int cdist[MAXN][MAXC + 1];

void solve() {
  int N, M, C; cin >> N >> M >> C;
  while (M--) {
    int u, v, w; cin >> u >> v >> w; --u; --v;
    adj[u].emplace_back(v, w);
  }

  using T = tuple<int, int, int>;
  priority_queue<T, vector<T>, greater<T>> pq;
  memset(cdist, 0x3f, sizeof(cdist)); cdist[0][0] = 0;

  for (int i = 0; i < C; ++i) {
    for (int j = 0; j < N; ++j) pq.emplace(cdist[j][i], j, i);

    while (!pq.empty()) {
      auto [d, u, c] = pq.top(); pq.pop();
      if (cdist[u][c] < d) continue;

      for (auto [v, w] : adj[u]) {
        if (cdist[v][c] > cdist[u][c] + w) {
          cdist[v][c] = cdist[u][c] + w;
          pq.emplace(cdist[v][c], v, c);
        }
        if (c < C && cdist[v][c + 1] > cdist[u][c] - w) {
          cdist[v][c + 1] = cdist[u][c] - w;
        }
      }
    }
  }

  int ans = 0x3f3f3f3f;
  for (int i = 0; i <= C; ++i) ans = min(ans, cdist[N - 1][i]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
