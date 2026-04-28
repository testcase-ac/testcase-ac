#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXP = 800, INF = 0x3f3f3f3f;
int cdist[MAXP + 1], P;
vector<pii> adj[MAXP + 1];

void dijk(int s) {
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  fill(cdist, cdist + P + 1, INF);
  pq.emplace(0, s); cdist[s] = 0;

  while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (cdist[u] < d) continue;
    for (auto [v, w] : adj[u]) {
      if (cdist[v] > cdist[u] + w) {
        cdist[v] = cdist[u] + w;
        pq.emplace(cdist[v], v);
      }
    }
  }
}

void solve() {
  int N, C; cin >> N >> P >> C;

  vector<int> cows;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    cows.push_back(x);
  }
  while (C--) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  int ans = INF;
  for (int i = 1; i <= P; ++i) {
    dijk(i);

    int ok = 1, sum = 0;
    for (int x : cows) {
      if (cdist[x] == INF) {
        ok = 0;
        break;
      }
      sum += cdist[x];
    }
    if (ok) ans = min(ans, sum);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
