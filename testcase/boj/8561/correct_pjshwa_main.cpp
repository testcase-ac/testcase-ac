#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
vector<pii> adj[MAXN + 1];
int cdist[MAXN + 1];

void solve() {
  int n, k, m; cin >> n >> k >> m;
  memset(cdist, 0x3f, sizeof(cdist));

  priority_queue<pii, vector<pii>, greater<pii>> pq;
  while (k--) {
    int x; cin >> x;
    cdist[x] = 0; pq.push({0, x});
  }
  while (m--) {
    int a, b, d; cin >> a >> b >> d;
    adj[a].push_back({b, d}); adj[b].push_back({a, d});
  }

  while (!pq.empty()) {
    auto [dist, u] = pq.top(); pq.pop();
    if (cdist[u] < dist) continue;
    for (auto [v, w] : adj[u]) {
      if (cdist[v] > cdist[u] + w) {
        cdist[v] = cdist[u] + w;
        pq.push({cdist[v], v});
      }
    }
  }

  int ans = 0;
  for (int i = 1; i <= n; ++i) ans = max(ans, cdist[i]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
