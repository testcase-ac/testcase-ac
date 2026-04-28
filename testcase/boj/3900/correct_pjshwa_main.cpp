#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, INF = 0x3f3f3f3f;
int parent[MAXN + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

int n, m;
void solve() {
  vector<tuple<int, int, int>> edges;
  set<int> uw;
  while (m--) {
    int u, v, w; cin >> u >> v >> w;
    edges.emplace_back(w, u, v);
    uw.insert(w);
  }
  sort(edges.begin(), edges.end());

  int ans = INF;
  for (int wmin : uw) {
    int uc = 0, wmax = 0;
    iota(parent, parent + n + 1, 0);

    for (auto& [w, u, v] : edges) {
      if (w < wmin) continue;
      if (Find(u) == Find(v)) continue;
      Union(u, v); ++uc;
      wmax = w;
    }

    if (uc == n - 1) ans = min(ans, wmax - wmin);
  }

  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  while (cin >> n >> m) {
    if (n == 0 && m == 0) break;
    solve();
  }
}
