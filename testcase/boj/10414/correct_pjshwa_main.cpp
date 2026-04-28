#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, INF = 0x3f3f3f3f;
int ban[MAXN + 1], parent[MAXN + 1], cdist[MAXN + 1][MAXN + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

void quit() {
  cout << "impossible\n";
}

void solve() {
  int N, M, P, x; cin >> N >> M >> P;
  vector<int> Ps(P);
  for (int i = 0; i < P; ++i) {
    cin >> Ps[i];
    ban[Ps[i]] = true;
  }

  vector<tuple<int, int, int>> edges;
  memset(cdist, 0x3f, sizeof(cdist));
  while (M--) {
    int u, v, w; cin >> u >> v >> w;
    if (!ban[u] && !ban[v]) edges.emplace_back(w, u, v);
    cdist[u][v] = min(cdist[u][v], w);
    cdist[v][u] = min(cdist[v][u], w);
  }
  sort(edges.begin(), edges.end());

  ll ans = 0;
  if (N == P) {
    for (int v1 = 1; v1 <= N; ++v1) for (int v2 = v1 + 1; v2 <= N; ++v2) {
      if (cdist[v1][v2] == INF) return quit();
      ans += cdist[v1][v2];
    }
    return cout << ans << '\n', void();
  }

  int uc = 0;
  iota(parent, parent + N + 1, 0);
  for (auto& [w, u, v] : edges) {
    if (Find(u) == Find(v)) continue;
    Union(u, v);
    ans += w; ++uc;
  }
  if (uc != N - P - 1) return quit();

  for (int i = 0; i < P; ++i) {
    int reach = INF;
    for (int v = 1; v <= N; ++v) {
      if (!ban[v]) reach = min(reach, cdist[Ps[i]][v]);
    }
    if (reach == INF) return quit();
    ans += reach;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
