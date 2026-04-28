#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
bool vis[MAX + 1];

pii maxd(int v, int d) {
  vis[v] = true;

  int mv = v, md = d;
  for (int u : graph[v]) {
    if (!vis[u]) {
      auto [dv, dd] = maxd(u, d + 1);
      if (md < dd) md = dd, mv = dv;
    }
  }

  return {mv, md};
}

void solve() {
  int N; cin >> N;

  vector<int> pl{1}; int it = 1;
  for (int i = 1; i <= N; i++) {
    int C; cin >> C;

    vector<int> nl;
    for (int i = 0; i < C; i++) nl.push_back(++it);
    for (int i = 0; i < C; i++) {
      int j = min(i, (int)pl.size() - 1);
      graph[pl[j]].push_back(nl[i]);
      graph[nl[i]].push_back(pl[j]);
    }

    pl = nl;
  }

  memset(vis, 0, sizeof(vis));
  int v1 = maxd(1, 0).first;
  memset(vis, 0, sizeof(vis));
  cout << maxd(v1, 0).second << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
