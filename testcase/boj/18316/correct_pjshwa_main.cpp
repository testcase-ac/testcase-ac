#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 1000, INF = 1e18;
ll d[MAX + 1][MAX + 1];
vector<int> adj[MAX + 1];
int C, A[MAX + 1];

ll r(int i, int c) {
  if (d[i][c] != -1) return d[i][c];

  ll ret = i == 1 ? 0 : -INF;
  for (int u : adj[i]) {
    if (c == MAX) break;
    ret = max(ret, r(u, c + 1) + A[u] - C * (2 * c + 1));
  }
  return d[i][c] = ret;
}

void solve() {
  int N, M; cin >> N >> M >> C;
  for (int i = 1; i <= N; ++i) cin >> A[i];
  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
  }

  memset(d, -1, sizeof(d));
  cout << r(1, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
