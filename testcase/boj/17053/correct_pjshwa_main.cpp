#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 300, MAXT = 2e5;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
char board[MAXN + 1][MAXN + 1];
vector<pair<pii, int>> H[MAXN + 1], V[MAXN + 1];
bool vis[MAXN + 1][MAXN + 1];
int parent[MAXT];

int Find(int x) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

void solve() {
  int N; cin >> N;

  map<pii, vector<int>> T;
  for (int i = 0; i < N; ++i) {
    int y1, x1, y2, x2; cin >> y1 >> x1 >> y2 >> x2;
    if (x1 == x2) H[x1].emplace_back(make_pair(min(y1, y2), max(y1, y2)), i);
    else V[y1].emplace_back(make_pair(min(x1, x2), max(x1, x2)), i);
    T[make_pair(x1, y1)].push_back(i);
    T[make_pair(x2, y2)].push_back(i);
  }
  for (int x = 0; x <= MAXN; ++x) fill(board[x], board[x] + MAXN + 1, '.');

  iota(parent, parent + MAXT, 0);
  for (const auto& [p, ids] : T) {
    int o = ids[0];
    for (auto id : ids) Union(o, id);
  }

  int ty, tx, g = -1; cin >> ty >> tx;
  for (int t = 0; t <= MAXN; ++t) {
    for (auto& [p, id] : H[t]) {
      auto [y1, y2] = p;
      if (tx == t && y1 <= ty && ty <= y2) g = Find(id);
    }
    for (auto& [p, id] : V[t]) {
      auto [x1, x2] = p;
      if (ty == t && x1 <= tx && tx <= x2) g = Find(id);
    }
  }

  for (int x = 0; x <= MAXN; ++x) {
    int Z = H[x].size(), pi = 0;
    sort(H[x].begin(), H[x].end());
    for (int y = 0; y <= MAXN; ++y) {
      while (pi < Z && H[x][pi].first.second < y) pi++;
      if (pi == Z) break;
      auto [l, u] = H[x][pi].first; int cg = Find(H[x][pi].second);
      if (l <= y && y <= u && cg == g) board[x][y] = '#';
    }
    // for (const auto& [y1, y2] : H[x]) {
    //   for (int y = y1; y <= y2; ++y) board[x][y] = '#';
    // }
  }
  for (int y = 0; y <= MAXN; ++y) {
    int Z = V[y].size(), pi = 0;
    sort(V[y].begin(), V[y].end());
    for (int x = 0; x <= MAXN; ++x) {
      while (pi < Z && V[y][pi].first.second < x) pi++;
      if (pi == Z) break;
      auto [l, u] = V[y][pi].first; int cg = Find(V[y][pi].second);
      if (l <= x && x <= u && cg == g) board[x][y] = '#';
    }
    // for (const auto& [x1, x2] : V[y]) {
    //   for (int x = x1; x <= x2; ++x) board[x][y] = '#';
    // }
  }

  int minx = MAXN, maxx = 0, miny = MAXN, maxy = 0;
  for (int x = 0; x <= MAXN; ++x) for (int y = 0; y <= MAXN; ++y) {
    if (board[x][y] != '#') continue;
    minx = min(minx, x), maxx = max(maxx, x);
    miny = min(miny, y), maxy = max(maxy, y);
  }
  for (int x = maxx; x >= minx; --x) {
    for (int y = miny; y <= maxy; ++y) cout << board[x][y];
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
