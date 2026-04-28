#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5, INF = 0x3f3f3f3f;
vector<int> adj[MAXN + 1];
int dp_l[MAXN + 1], k;

void dfs1(int u, int p) {
  int fi = 0, se = 0;
  for (int v : adj[u]) {
    if (v == p) continue;
    dfs1(v, u);

    if (dp_l[v] > fi) se = fi, fi = dp_l[v];
    else if (dp_l[v] > se) se = dp_l[v];
  }

  if (fi + se >= k) dp_l[u] = 0;
  else dp_l[u] = fi + 1;
}

void solve() {
  int N; cin >> N >> k;
  for (int i = 0; i < N - 1; ++i) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v); adj[v].push_back(u);
  }

  dfs1(1, -1); int ans = 0;
  for (int i = 1; i <= N; ++i) ans += (dp_l[i] == 0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
