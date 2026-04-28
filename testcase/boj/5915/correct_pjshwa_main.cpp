#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 40000, MAXW = 1e6, MOD = 1e9 + 7;
vector<pii> by_w[MAXW + 1];
int parent[MAXN + 1], pre_parent[MAXN + 1];

int Find(int x) {
  if (parent[x] == x) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

void solve() {
  int N, M; cin >> N >> M;

  iota(parent, parent + N + 1, 0);
  for (int i = 0; i < M; ++i) {
    int u, v, w; cin >> u >> v >> w;
    by_w[w].emplace_back(u, v);
  }

  ll wgt = 0, cnt = 1;
  for (int w = 1; w <= MAXW; ++w) {
    if (by_w[w].empty()) continue;

    vector<int> R;
    for (auto& [u, v] : by_w[w]) {
      R.push_back(u); R.push_back(v);
      R.push_back(Find(u)); R.push_back(Find(v));
    }
    for (int e : R) pre_parent[e] = parent[e];

    int mgc = 0;
    for (auto& [u, v] : by_w[w]) {
      if (Find(u) == Find(v)) continue;
      Union(u, v);
      ++mgc;
      wgt = (wgt + w) % MOD;
    }

    int Z = by_w[w].size(), cur = 0;
    for (int s = 0; s < (1 << Z); ++s) {
      if (__builtin_popcount(s) != mgc) continue;

      for (int e : R) parent[e] = pre_parent[e];

      int mgc_c = 0;
      for (int i = 0; i < Z; ++i) {
        if (!(s & (1 << i))) continue;

        auto& [u, v] = by_w[w][i];
        if (Find(u) == Find(v)) continue;

        Union(u, v); ++mgc_c;
      }
      if (mgc_c == mgc) ++cur;
    }

    for (int e : R) parent[e] = pre_parent[e];
    for (auto& [u, v] : by_w[w]) {
      if (Find(u) != Find(v)) Union(u, v);
    }

    cnt = cnt * cur % MOD;
  }

  cout << wgt << ' ' << cnt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
