#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int parent[MAXN];

int Find(int x) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

int N;
void solve() {
  vector<pii> points;
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    points.emplace_back(x, y);
  }

  vector<tuple<int, int, int>> edges;
  for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
    auto [x1, y1] = points[i]; auto [x2, y2] = points[j];
    int dist = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    edges.emplace_back(dist, i, j);
  }
  sort(edges.begin(), edges.end());

  iota(parent, parent + N, 0); double ans = 0;
  for (auto& [d, u, v] : edges) {
    if (Find(u) == Find(v)) continue;
    Union(u, v);
    ans += sqrt(d);
  }
  cout << fixed << setprecision(2) << ans << '\n';
}

int main() {
  fast_io();

  while (cin >> N) {
    if (N == 0) break;
    solve();
  }
}
