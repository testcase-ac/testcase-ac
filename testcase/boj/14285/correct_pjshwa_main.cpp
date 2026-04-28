#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000, MAXC = 100, INF = 0x3f3f3f3f;
vector<pii> adj[MAXN + 1];
int cdist[MAXN + 1][MAXC + 1];

void solve() {
  int N, M; cin >> N >> M;

  int total = 0;
  while (M--) {
    int a, b, c; cin >> a >> b >> c;
    adj[a].emplace_back(b, c);
    adj[b].emplace_back(a, c);
    total += c;
  }
  int S, T; cin >> S >> T;

  memset(cdist, 0x3f, sizeof(cdist));
  priority_queue<tii, vector<tii>, greater<tii>> pq;
  cdist[S][0] = 0; pq.emplace(0, S, 0);

  while (!pq.empty()) {
    auto [d, u, c] = pq.top(); pq.pop();
    if (cdist[u][c] < d) continue;
    for (auto [v, w] : adj[u]) {
      int nc = max(c, w);
      if (cdist[v][nc] > d + w) {
        cdist[v][nc] = d + w;
        pq.emplace(d + w, v, nc);
      }
    }
  }

  int ans = 0;
  for (int c = 0; c <= MAXC; ++c) {
    if (cdist[T][c] == INF) continue;
    ans = max(ans, total - cdist[T][c] + c);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
