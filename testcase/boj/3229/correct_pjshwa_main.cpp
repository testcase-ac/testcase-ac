#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
vector<int> adj[MAXN + 1];
int cdist[MAXN + 1];

void solve() {
  int N, M; cin >> N >> M;
  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v); adj[v].push_back(u);
  }

  memset(cdist, 0x3f, sizeof(cdist));
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  cdist[1] = 0; pq.push({0, 1});

  while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (cdist[u] < d) continue;

    for (int v : adj[u]) {
      int mov = abs(u - v), intv = 2 * mov;
      int r = d % intv;
      int nd = d + (r == 0 ? 0 : intv - r) + mov;
      if (cdist[v] > nd) cdist[v] = nd, pq.push({nd, v});
    }
  }

  cout << (ll)cdist[N] * 5 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
