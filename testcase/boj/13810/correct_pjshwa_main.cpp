#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 40000;
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
vector<pii> adj[MAXN];
int color[MAXN], f;

void dfs(int v, int c) {
  if (f) return;

  color[v] = c;
  for (auto& [u, x] : adj[v]) {
    if (color[u] == -1) {
      dfs(u, c ^ x);
    }
    else if (color[u] != (c ^ x)) {
      f = 1;
      return;
    }
  }
}

int N;
void solve() {
  for (int i = 0; i < 2 * N; ++i) {
    adj[i].clear();
    color[i] = -1;
  }

  map<pii, int> G;
  for (int i = 0; i < N; ++i) {
    int x, y; string s; cin >> x >> y >> s;
    if (s == "x") {
      G[{x, y}] = i;
      G[{x + 1, y}] = i + N;
    }
    else {
      G[{x, y}] = i;
      G[{x, y + 1}] = i + N;
    }
  }

  for (auto& [p, i] : G) {
    auto [x, y] = p;
    for (int d = 0; d < 4; ++d) {
      int nx = x + dx[d], ny = y + dy[d];
      if (!G.count({nx, ny})) continue;
      
      int idiff = abs(i - G[{nx, ny}]);
      adj[i].emplace_back(G[{nx, ny}], idiff == N);
    }
  }

  f = 0;
  for (int u = 0; u < 2 * N; ++u) {
    if (color[u] == -1) dfs(u, 0);
  }
  if (f) cout << "No\n";
  else cout << "Yes\n";
}

int main() {
  fast_io();

  while (cin >> N) {
    if (N == 0) break;
    solve();
  }
}
