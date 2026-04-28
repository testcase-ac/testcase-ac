#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2500;
vector<pii> adj[MAXN + 1];
int A[MAXN + 1];
ll cdist[MAXN + 1][MAXN + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= N; ++i) {
    cin >> A[i];
    fill(cdist[i], cdist[i] + MAXN + 1, 1e18);
  }

  while (M--) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  using tli = tuple<ll, int, int>;
  priority_queue<tli, vector<tli>, greater<tli>> pq;
  pq.emplace(0, 1, A[1]); cdist[1][A[1]] = 0;

  while (!pq.empty()) {
    auto [dist, u, unit] = pq.top(); pq.pop();
    if (cdist[u][unit] < dist) continue;

    for (auto [v, w] : adj[u]) {
      ll ndist = dist + unit * w;
      int nunit = min(unit, A[v]);
      if (cdist[v][nunit] > ndist) {
        cdist[v][nunit] = ndist;
        pq.emplace(ndist, v, nunit);
      }
    }
  }

  ll ans = 1e18;
  for (int unit = 0; unit <= MAXN; ++unit) {
    ans = min(ans, cdist[N][unit]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
