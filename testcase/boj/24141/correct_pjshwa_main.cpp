#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5, INF = 0x3f3f3f3f;
int X[MAXN], Y[MAXN];
vector<int> adj[MAXN];

void solve() {
  int N, M, D, K; cin >> N >> M >> D >> K;

  map<pii, int> G_inv;
  for (int i = 0; i < N; ++i) {
    cin >> X[i] >> Y[i];
    G_inv[{X[i], Y[i]}] = i;
  }

  vector<pii> ds;
  for (int dx = -25; dx <= 25; ++dx) for (int dy = -25; dy <= 25; ++dy) {
    if (dx == 0 && dy == 0) continue;
    if (dx * dx + dy * dy <= D * D) ds.emplace_back(dx, dy);
  }

  for (int i = 0; i < N; ++i) for (auto [dx, dy] : ds) {
    int nx = X[i] + dx, ny = Y[i] + dy;
    if (G_inv.count({nx, ny})) {
      adj[i].push_back(G_inv[{nx, ny}]);
    }
  }

  vector<int> cdist(N, INF);
  queue<int> q;
  q.push(0); cdist[0] = 0;

  while (!q.empty()) {
    int cv = q.front(); q.pop();
    for (int nv : adj[cv]) {
      if (cdist[nv] > cdist[cv] + 1) {
        cdist[nv] = cdist[cv] + 1;
        q.push(nv);
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    ans += cdist[i] <= K && cdist[i] + M > K;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
