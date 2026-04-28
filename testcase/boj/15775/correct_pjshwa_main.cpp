#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2.5e5;
vector<pii> adj[MAXN + 1];
ll S[MAXN + 1];

void solve() {
  int N, M; cin >> N >> M;

  vector<tuple<int, int, int>> edges(M);
  for (int i = 0; i < M; ++i) {
    int u, v, w; cin >> u >> v >> w;
    edges[i] = {u, v, w};
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  using tu = tuple<ll, int, int>;
  priority_queue<tu, vector<tu>, greater<tu>> pq;
  vector<pair<ll, int>> dist(N + 1, {LLONG_MAX, N + 1});

  int K; cin >> K;
  vector<int> P(K);
  for (int i = 0; i < K; ++i) {
    int u; cin >> u;
    P[i] = u;
    pq.emplace(0, u, u); dist[u] = {0, u};
  }

  while (!pq.empty()) {
    auto [d, p, u] = pq.top(); pq.pop();
    if (dist[u].first < d) continue;

    for (auto [v, w] : adj[u]) {
      if (dist[v].first > d + w || (dist[v].first == d + w && dist[v].second > p)) {
        dist[v] = {d + w, p};
        pq.emplace(d + w, p, v);
      }
    }
  }

  for (auto& [u, v, w] : edges) {
    auto [ud, up] = dist[u]; auto [vd, vp] = dist[v];
    if (ud < vd) {
      ll dif = vd - ud;
      S[up] += w + dif;
      S[vp] += w - dif;
    }
    else {
      ll dif = ud - vd;
      S[up] += w - dif;
      S[vp] += w + dif;
    }
  }

  for (int p : P) {
    if (S[p] % 2 == 0) cout << S[p] / 2 << ".0\n";
    else cout << S[p] / 2 << ".5\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
