#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
const int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
const int dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};
int parent[MAXN + 1];

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

  vector<pii> points(N);
  map<pii, int> p_map;
  for (int i = 0; i < N; ++i) {
    int xi, yi; cin >> xi >> yi;
    points[i] = {xi, yi};
    p_map[{xi, yi}] = i;
  }

  iota(parent, parent + N, 0);
  for (int i = 0; i < N; ++i) {
    auto [xi, yi] = points[i];
    for (int k = 0; k < 8; ++k) {
      int nxi = xi + dx[k], nyi = yi + dy[k];
      if (p_map.count({nxi, nyi})) {
        Union(i, p_map[{nxi, nyi}]);
      }
    }
  }

  set<int> groups;
  map<int, int> g_dist;
  for (int i = 0; i < N; ++i) groups.insert(Find(i));
  for (int i = 0; i < N; ++i) {
    auto [xi, yi] = points[i];
    int g = Find(i), dist = abs(xi) + abs(yi);
    if (g_dist.count(g)) g_dist[g] = min(g_dist[g], dist);
    else g_dist[g] = dist;
  }

  vector<ll> dists;
  for (auto& [g, dist] : g_dist) dists.push_back(dist);
  sort(dists.begin(), dists.end(), greater<>());

  ll ans = dists[0];
  for (int i = 1; i < (int)dists.size(); ++i) ans += 2 * dists[i];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
