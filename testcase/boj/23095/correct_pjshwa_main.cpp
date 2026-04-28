#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, MAXZ = 10000;
char board[MAXN + 1][MAXN + 1];
vector<int> adj[MAXZ];
bool vis[MAXZ];

bool reachable(int x1, int y1, int x2, int y2, char t) {
  if (t == 'R') {
    return x1 == x2 || y1 == y2;
  }
  if (t == 'Q') {
    return x1 == x2 || y1 == y2 || abs(x1 - x2) == abs(y1 - y2);
  }
  if (t == 'B') {
    return abs(x1 - x2) == abs(y1 - y2);
  }
  if (t == 'N') {
    return abs(x1 - x2) + abs(y1 - y2) == 3 && abs(x1 - x2) * abs(y1 - y2) == 2;
  }
  if (t == 'K') {
    return abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1;
  }
}

vector<pii> points;
void dfs(int u, int s) {
  vis[u] = true;
  for (int v : adj[u]) {
    if (vis[v]) continue;

    dfs(v, s);
    if (s) {
      auto [ux, uy] = points[u]; auto [vx, vy] = points[v];
      cout << vx << ' ' << vy << ' ' << ux << ' ' << uy << '\n';
    }
  }
}

void solve() {
  int N; string Ts; cin >> N >> Ts;
  char T = Ts[0];
  for (int i = 0; i < N; ++i) cin >> board[i];

  // check if we can make a spanning tree
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    if (board[i][j] == T) points.emplace_back(i + 1, j + 1);
  }

  int Z = points.size();
  for (int i = 0; i < Z; ++i) for (int j = i + 1; j < Z; ++j) {
    auto [xi, yi] = points[i]; auto [xj, yj] = points[j];
    if (reachable(xi, yi, xj, yj, T)) {
      adj[i].push_back(j);
      adj[j].push_back(i);
    }
  }

  memset(vis, false, sizeof(vis));
  dfs(0, 0);
  for (int i = 0; i < Z; ++i) {
    if (!vis[i]) return cout << "NO\n", void();
  }

  cout << "YES\n";
  memset(vis, false, sizeof(vis));
  dfs(0, 1);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
