#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e4;
const ll INF = 1e18;
ll cdist[21][MAX + 1];
vector<pii> graph[MAX + 1];

void solve() {
  int N, M, K;
  cin >> N >> M >> K;
  while (M--) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].emplace_back(v, w);
    graph[v].emplace_back(u, w);
  }

  for (int i = 0; i <= 20; i++) fill(cdist[i], cdist[i] + N + 1, INF);

  using tiii = tuple<ll, int, int>;
  priority_queue<tiii, vector<tiii>, greater<tiii>> pq;
  pq.emplace(0, 1, 0);
  cdist[0][1] = 0;

  while (!pq.empty()) {
    auto [d, u, k] = pq.top(); pq.pop();

    if (d > cdist[k][u]) continue;

    for (auto [v, w] : graph[u]) {
      if (cdist[k][v] > d + w) {
        cdist[k][v] = d + w;
        pq.emplace(cdist[k][v], v, k);
      }
      if (k < K && cdist[k + 1][v] > d) {
        cdist[k + 1][v] = d;
        pq.emplace(cdist[k + 1][v], v, k + 1);
      }
    }
  }

  ll ans = INF;
  for (int i = 0; i <= K; i++) ans = min(ans, cdist[i][N]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
