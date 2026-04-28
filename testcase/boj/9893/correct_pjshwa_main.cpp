#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, MAXT = 100, INF = 0x3f3f3f3f;
int cost[MAXT + 1][MAXN];
vector<pii> adj[MAXN];

void solve() {
  int N, M; cin >> N >> M;
  while (M--) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
  }

  memset(cost, 0x3f, sizeof(cost)); cost[0][0] = 0;
  for (int t = 0; t < MAXT; ++t) for (int s = 0; s < N; ++s) {
    for (auto [e, w] : adj[s]) {
      cost[t + 1][e] = min(cost[t + 1][e], cost[t][s] + w);
    }
  }

  for (int t = 0; t <= MAXT; ++t) {
    // cout << "t = " << t << ", cost = " << cost[t][1] << '\n';
    if (cost[t][1] != INF) return cout << cost[t][1] << '\n', void();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
