#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
vector<int> gf[MAX + 1], gb[MAX + 1];
bool visf[MAX + 1], visb[MAX + 1];
set<pii> edges;

void dfsf(int u) {
  visf[u] = true;
  for (int v : gf[u]) {
    if (!visf[v]) {
      edges.insert({u, v});
      dfsf(v);
    }
  }
}

void dfsb(int u) {
  visb[u] = true;
  for (int v : gb[u]) {
    if (!visb[v]) {
      edges.insert({v, u});
      dfsb(v);
    }
  }
}

void solve() {
  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    gf[i].clear();
    gb[i].clear();
    visf[i] = false;
    visb[i] = false;
  }

  vector<pii> E;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    gf[u].push_back(v);
    gb[v].push_back(u);
    E.push_back({u, v});
  }

  edges.clear();
  dfsf(1);
  dfsb(1);

  int skips = m - 2 * n;
  for (auto& p : E) {
    if (skips == 0) break;
    if (edges.count(p)) continue;

    cout << p.first << ' ' << p.second << '\n';
    skips--;
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
