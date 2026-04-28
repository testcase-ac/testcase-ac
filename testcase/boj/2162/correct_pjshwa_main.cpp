#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

ll ccw(pll a, pll b, pll c) {
  ll u = (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
  if (u > 0) return 1;
  else if (u == 0) return 0;
  else return -1;
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
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

const int MAX = 3000;
int parent[MAX], usz[MAX];
Segment ss[MAX];

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

  if (x == y) return;

  parent[y] = x;
  usz[x] += usz[y];
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    ss[i] = {pll{x1, y1}, pll{x2, y2}};
    parent[i] = i, usz[i] = 1;
  }

  for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
    if (intersects(ss[i], ss[j])) Union(i, j);
  }

  set<int> groups;
  for (int i = 0; i < n; i++) groups.insert(Find(i));

  int msize = 0;
  for (int g : groups) msize = max(msize, usz[g]);

  cout << groups.size() << '\n' << msize << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
