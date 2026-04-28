#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 1e4, INF = 1e18;
ll cdist[MAX], ban[MAX + 1], vis[MAX];
vector<tll> adj[MAX], adj_inv[MAX];

void dijk(int s) {
  fill(cdist, cdist + MAX + 1, INF);
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto& [vi, di, ei] : adj[ui]) {
      if (ban[ei]) continue;
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

int N, M;
void solve() {
  int S, D; cin >> S >> D;

  for (int i = 0; i < N; i++) {
    adj[i].clear();
    adj_inv[i].clear();
  }
  memset(ban, 0, sizeof(ban));

  for (int i = 1; i <= M; i++) {
    int U, V, P; cin >> U >> V >> P;
    adj[U].push_back({V, P, i});
    adj_inv[V].push_back({U, P, i});
  }

  dijk(S);
  ll d = cdist[D];

  memset(vis, 0, sizeof(vis));

  queue<int> q;
  q.push(D);
  vis[D] = 1;

  while (!q.empty()) {
    int v = q.front(); q.pop();
    for (auto& [u, p, i] : adj_inv[v]) {
      if (cdist[u] + p == cdist[v]) {
        ban[i] = 1;
        if (!vis[u]) {
          vis[u] = 1;
          q.push(u);
        }
      }
    }
  }

  dijk(S);
  cout << (cdist[D] == INF ? -1 : cdist[D]) << '\n';
}

int main() {
  fast_io();

  while (cin >> N >> M) {
    if (N == 0 && M == 0) break;
    solve();
  }
}
