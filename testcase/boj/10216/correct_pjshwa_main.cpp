#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int parent[3000];
tuple<int, int, int> g[3000];

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

bool overlaps(tuple<int, int, int>& g1, tuple<int, int, int>& g2) {
  auto[x1, y1, r1] = g1;
  auto[x2, y2, r2] = g2;
  return (r1 + r2) * (r1 + r2) >= (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

int main() {
  fast_io();

  int t, n, x, y, r;
  cin >> t;

  while (t--) {
    cin >> n;

    for (int i = 0; i < n; i++) parent[i] = i;
    for (int i = 0; i < n; i++) {
      cin >> x >> y >> r;
      g[i] = {x, y, r};
    }

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (overlaps(g[i], g[j])) Union(i, j);
      }
    }

    set<int> ans;
    for (int i = 0; i < n; i++) ans.insert(Find(i));
    cout << ans.size() << '\n';
  }
}
