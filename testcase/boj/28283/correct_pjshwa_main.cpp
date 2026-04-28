#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5, INF = 0x3f3f3f3f;
ll A[MAX + 1], cdist[MAX + 1];
vector<int> adj[MAX + 1];

void solve() {
  int N, M, X, Y; cin >> N >> M >> X >> Y;
  for (int i = 1; i <= N; i++) cin >> A[i];
  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  fill(cdist, cdist + N + 1, INF);
  queue<int> q;
  while (Y--) {
    int x; cin >> x;
    cdist[x] = 0; q.push(x);
  }

  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
      if (cdist[v] == INF) {
        cdist[v] = cdist[u] + 1;
        q.push(v);
      }
    }
  }

  for (int i = 1; i <= N; i++) {
    if (A[i] > 0 && cdist[i] == INF) return cout << "-1\n", void();
    cdist[i] *= A[i];
  }
  sort(cdist + 1, cdist + N + 1, greater<int>());

  ll ans = 0;
  for (int i = 1; i <= X; i++) ans += cdist[i];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
