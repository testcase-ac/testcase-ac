#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
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

const int MAX = 2500;
vector<int> graph[MAX];
int indegree[MAX];

void solve() {
  int N;
  cin >> N;

  vector<tuple<int, int, int, int, int>> a(N);
  for (int i = 0; i < N; i++) {
    int sx, sy, ex, ey, wi;
    cin >> sx >> sy >> ex >> ey >> wi;
    a[i] = {sx, sy, ex, ey, wi};
  }

  for (int i = 0; i < N; i++) for (int j = 0; j < i; j++) {
    Segment x = {pll{get<0>(a[i]), get<1>(a[i])}, pll{get<2>(a[i]), get<3>(a[i])}};
    Segment y = {pll{get<0>(a[j]), get<1>(a[j])}, pll{get<2>(a[j]), get<3>(a[j])}};
    if (!intersects(x, y)) continue;

    int wx = get<4>(a[i]), wy = get<4>(a[j]);
    if (wx > wy) {
      graph[j].push_back(i);
      indegree[i]++;
    }
    else {
      graph[i].push_back(j);
      indegree[j]++;
    }
  }

  ll ans = 0;
  queue<int> q;
  for (int i = 0; i < N; i++) {
    if (!indegree[i]) q.push(i);
  }

  for (int i = 0; i < N; i++) {
    int v = q.front();
    q.pop();

    ll cur = get<4>(a[v]);
    cur *= (graph[v].size() + 1);
    ans += cur;

    for (int u : graph[v]) {
      if (!--indegree[u]) q.push(u);
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
