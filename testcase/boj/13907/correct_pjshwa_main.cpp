#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 1000, INF = 1e18;
ll cdist[MAXN + 1][MAXN + 1];
vector<pii> adj[MAXN + 1];

void solve() {
  int N, M, K, S, D; cin >> N >> M >> K >> S >> D;
  while (M--) {
    int a, b, w; cin >> a >> b >> w;
    adj[a].emplace_back(b, w);
    adj[b].emplace_back(a, w);
  }

  using T = tuple<ll, int, int>;
  priority_queue<T, vector<T>, greater<T>> pq;

  for (int i = 1; i <= N; ++i) fill(cdist[i], cdist[i] + MAXN + 1, INF);
  pq.emplace(0, S, 0); cdist[S][0] = 0;

  while (!pq.empty()) {
    auto [cost, u, l] = pq.top(); pq.pop();
    if (cdist[u][l] < cost) continue;

    for (auto [v, w] : adj[u]) {
      ll ncost = cost + w;
      if (l < N && cdist[v][l + 1] > ncost) {
        cdist[v][l + 1] = ncost;
        pq.emplace(ncost, v, l + 1);
      }
    }
  }

  ll ans = INF, lu = -1;
  for (int i = 0; i <= N; ++i) {
    if (ans <= cdist[D][i]) continue;
    ans = cdist[D][i];
    lu = i;
  }
  cout << ans << '\n';

  auto cost_ew = [&](int used, ll extra) {
    return cdist[D][used] + extra * used;
  };

  ll ew = 0;
  while (K--) {
    int x; cin >> x;
    ew += x;

    ll ans = INF;
    for (int i = 0; i <= N; ++i) ans = min(ans, cost_ew(i, ew));
    cout << ans << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
