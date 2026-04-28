#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 500;
vector<int> adj[MAX + 1];
bool edg[MAX + 1][MAX + 1];
int deg[MAX + 1];

vector<pii> tri[MAX + 1];
int tri_len[MAX + 1][MAX + 1];

ll nC2(int n) {
  return (ll)n * (n - 1) / 2;
}

void solve() {
  int N, M; cin >> N >> M;
  while (M--) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v); adj[v].push_back(u);
    edg[u][v] = edg[v][u] = true;
    deg[u]++; deg[v]++;
  }

  for (int u = 1; u <= N; u++) {
    int z = deg[u];
    for (int i = 0; i < z; i++) for (int j = i + 1; j < z; j++) {
      int v1 = adj[u][i], v2 = adj[u][j];
      if (edg[v1][v2]) {
        tri[u].emplace_back(v1, v2);
        tri_len[v1][v2]++;
        tri_len[v2][v1]++;
      }
    }
  }

  ll ans = 0;
  for (int u = 1; u <= N; u++) {
    if (deg[u] < 6) continue;

    // take 2 triangles
    for (auto [v1, v2] : tri[u]) {
      ll avail = tri[u].size() + 1 - tri_len[u][v1] - tri_len[u][v2];
      ans += avail * nC2(deg[u] - 4);
    }
  }
  cout << ans / 2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
