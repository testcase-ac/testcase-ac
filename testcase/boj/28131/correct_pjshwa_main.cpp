#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e4, MAXK = 50, INF = 0x3f3f3f3f;
int cdist[MAX + 1][MAXK];
vector<pii> adj[MAX + 1];

void solve() {
  int N, M, K, S, T; cin >> N >> M >> K >> S >> T;
  while (M--) {
    int u, v, c; cin >> u >> v >> c;
    adj[u].emplace_back(v, c);
  }

  memset(cdist, 0x3f, sizeof(cdist));
  priority_queue<tii, vector<tii>, greater<tii>> pq;
  pq.emplace(0, S, 0); cdist[S][0] = 0;

  while (!pq.empty()) {
    auto [wi, ui, ki] = pq.top(); pq.pop();
    if (wi > cdist[ui][ki]) continue;

    for (auto& [vi, ci] : adj[ui]) {
      int nki = (ki + ci) % K;
      if (cdist[vi][nki] > wi + ci) {
        cdist[vi][nki] = wi + ci;
        pq.emplace(cdist[vi][nki], vi, nki);
      }
    }
  }

  int ans = cdist[T][0];
  if (ans == INF) cout << "IMPOSSIBLE\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
