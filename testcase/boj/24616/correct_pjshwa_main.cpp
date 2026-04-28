#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll dist(pll& a, pll& b) {
  return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

const int MAX = 1e5;
pll points[MAX];
int parent[MAX], sp[11];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    points[i] = {x, y};
  }
  for (int i = 0; i < n; i++) parent[i] = i;
  sort(points, points + n);
  memset(sp, -1, sizeof(sp));

  // Kruskal's algorithm
  vector<tuple<ll, int, int>> ta;
  for (int i = 0; i < n; i++) {
    auto& [ax, ay] = points[i];
    for (int j = 0; j <= 10; j++) {
      if (sp[j] == -1) continue;
      ta.push_back({dist(points[sp[j]], points[i]), i, sp[j]});
    }
    sp[ay] = i;
  }
  sort(ta.begin(), ta.end());

  ll ans = 0;
  for (auto& [w, x, y] : ta) {
    if (Find(x) == Find(y)) continue;
    ans += w;
    Union(x, y);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
