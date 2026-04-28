#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
vector<tuple<int, int, ll>> adj[MAX + 1][2];
ll cdist[MAX + 1][2];

void solve() {
  int N, M, K; cin >> N >> M >> K;

  while (M--) {
    int u, v, c; cin >> u >> v >> c;
    for (int k = 0; k < 2; ++k) {
      adj[u][k].emplace_back(v, k, c);
      adj[v][k].emplace_back(u, k, c);
    }
  }
  for (int i = 1; i <= N; ++i) {
    ll c; cin >> c;
    if (c == -1) continue;

    adj[i][0].emplace_back(i, 1, c * (K - 1));
    adj[i][1].emplace_back(i, 0, c * (K - 1));
  }

  for (int i = 1; i <= N; ++i) for (int k = 0; k < 2; ++k) cdist[i][k] = LLONG_MAX;

  using tli = tuple<ll, int, int>;
  priority_queue<tli, vector<tli>, greater<tli>> pq;
  pq.emplace(0, 1, 0); cdist[1][0] = 0;

  while (!pq.empty()) {
    auto [cd, u, k] = pq.top(); pq.pop();
    if (cd > cdist[u][k]) continue;

    for (auto [v, nk, c] : adj[u][k]) {
      if (cd + c < cdist[v][nk]) {
        cdist[v][nk] = cd + c;
        pq.emplace(cd + c, v, nk);
      }
    }
  }

  ll ans = cdist[N][1];
  if (ans == LLONG_MAX) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
