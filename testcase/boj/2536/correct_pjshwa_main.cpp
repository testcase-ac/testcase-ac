#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll ccw(pll a, pll b, pll c) {
  ll u = (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
  if (u > 0) return 1;
  else if (u == 0) return 0;
  else return -1;
}

struct Segment {
  pll x, y;
};

bool intersects(Segment x, Segment y) {
  ll abc = ccw(x.x, x.y, y.x), abd = ccw(x.x, x.y, y.y);
  ll cda = ccw(y.x, y.y, x.x), cdb = ccw(y.x, y.y, x.y);
  if (abc * abd == 0 && cda * cdb == 0) {
    if (x.x > x.y) swap(x.x, x.y);
    if (y.x > y.y) swap(y.x, y.y);
    return x.x <= y.y && y.x <= x.y;
  }
  else return abc * abd <= 0 && cda * cdb <= 0;
}

const int MAX = 5000;
vector<int> graph[MAX];
bool E[MAX], vis[MAX];

void solve() {
  int m, n, k;
  cin >> m >> n >> k;

  vector<Segment> L;
  for (int i = 0; i < k; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> x1 >> y1 >> x2 >> y2;
    L.emplace_back(Segment{pll{x1, y1}, pll{x2, y2}});
  }

  for (int i = 0; i < k; i++) for (int j = i + 1; j < k; j++) {
    if (intersects(L[i], L[j])) {
      graph[i].push_back(j);
      graph[j].push_back(i);
    }
  }

  queue<pll> q;

  int sx, sy, dx, dy;
  cin >> sx >> sy >> dx >> dy;
  for (int i = 0; i < k; i++) {
    auto [x1, y1] = L[i].x;
    auto [x2, y2] = L[i].y;

    if (x1 == x2 && x1 == sx && min(y1, y2) <= sy && sy <= max(y1, y2)) {
      q.push({i, 0});
      vis[i] = true;
    }
    else if (y1 == y2 && y1 == sy && min(x1, x2) <= sx && sx <= max(x1, x2)) {
      q.push({i, 0});
      vis[i] = true;
    }

    if (x1 == x2 && x1 == dx && min(y1, y2) <= dy && dy <= max(y1, y2)) {
      E[i] = true;
    }
    else if (y1 == y2 && y1 == dy && min(x1, x2) <= dx && dx <= max(x1, x2)) {
      E[i] = true;
    }
  }

  while (!q.empty()) {
    auto [u, c] = q.front(); q.pop();

    if (E[u]) return cout << c + 1 << '\n', void();

    for (int v : graph[u]) {
      if (!vis[v]) {
        vis[v] = true;
        q.push({v, c + 1});
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
