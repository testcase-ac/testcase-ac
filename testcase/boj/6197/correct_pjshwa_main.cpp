#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5000;
vector<pii> adj[MAX + 1];
int cdist[MAX + 1][2];

void solve() {
  int N, M; cin >> N >> M;
  while (M--) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  memset(cdist, 0x3f, sizeof(cdist));
  priority_queue<tii, vector<tii>, greater<tii>> pq;
  pq.emplace(0, 1, 0); cdist[1][0] = 0;

  while (!pq.empty()) {
    auto [d, v, t] = pq.top(); pq.pop();

    if (cdist[v][t] < d) continue;

    for (auto [u, w] : adj[v]) {
      if (cdist[u][0] > d + w) {
        cdist[u][1] = cdist[u][0];
        cdist[u][0] = d + w;
        pq.emplace(cdist[u][0], u, 0);
        pq.emplace(cdist[u][1], u, 1);
      }
      else if (cdist[u][1] > d + w && cdist[u][0] < d + w) {
        cdist[u][1] = d + w;
        pq.emplace(cdist[u][1], u, 1);
      }
    }
  }

  cout << cdist[N][1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
