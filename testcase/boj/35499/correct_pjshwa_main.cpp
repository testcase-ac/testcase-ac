#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int parent[MAXN], usz[MAXN], esz[MAXN];

int Find(int x) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x); y = Find(y);
  if (x == y) return;
  if (usz[x] < usz[y]) swap(x, y);
  parent[y] = x;
  usz[x] += usz[y];
  esz[x] += esz[y] + 1;
}

void solve() {
  int N, M; cin >> N >> M;
  vector<tuple<int, int, int>> edges;
  while (M--) {
    int u, v, w; cin >> u >> v >> w;
    edges.emplace_back(w, u - 1, v - 1);
  }
  sort(edges.begin(), edges.end(), greater<>());

  iota(parent, parent + N, 0);
  fill(usz, usz + N, 1);
  fill(esz, esz + N, 0);

  ll ans = 0;
  for (auto& [w, u, v] : edges) {
    int x = Find(u), y = Find(v);
    if (x != y) {
      if (esz[x] + esz[y] < usz[x] + usz[y]) {
        Union(x, y);
        ans += w;
      }
    } else if (esz[x] < usz[x]) {
      ++esz[x];
      ans += w;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
