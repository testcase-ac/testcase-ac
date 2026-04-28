#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500, MAXM = 50000, INF = 0x3f3f3f3f;
int N, M, U[MAXM], parent[MAXN], ban = -1;
vector<tuple<int, int, int, int>> edges;

int Find(int x) {
  if (parent[x] == x) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[x] = y;
}

int get() {
  iota(parent, parent + N, 0);
  fill(U, U + M, 0);
  int ret = 0, uc = 0;
  for (auto& [w, u, v, i] : edges) {
    if (i == ban) continue;
    if (Find(u) == Find(v)) continue;
    Union(u, v); ret += w; ++uc;
    U[i] = 1;
  }
  return uc == N - 1 ? ret : INF;
}

void solve() {
  cin >> N >> M;
  for (int i = 0; i < M; ++i) {
    int u, v, w; cin >> u >> v >> w; --u, --v;
    edges.emplace_back(w, u, v, i);
  }
  sort(edges.begin(), edges.end());

  int cost = get();
  vector<pair<int, int>> candidates;
  for (auto& [w, u, v, i] : edges) {
    if (U[i]) candidates.emplace_back(w, i);
  }

  int cnt = 0, wgt = 0;
  for (auto& [w, i] : candidates) {
    ban = i;
    int alt = get();
    if (alt > cost) cnt += 1, wgt += w;
  }
  cout << cnt << ' ' << wgt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
