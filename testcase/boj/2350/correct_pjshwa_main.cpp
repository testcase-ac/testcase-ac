#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int parent[MAX + 1];

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
  int n, m, k;
  cin >> n >> m >> k;

  vector<tii> edges(m);
  for (int i = 0; i < m; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    edges[i] = make_tuple(x, y, w);
  }

  vector<pii> queries(k);
  vector<int> ans(k);
  for (int i = 0; i < k; i++) {
    int x, y;
    cin >> x >> y;
    queries[i] = make_pair(x, y);
  }

  for (int wl = 1; wl <= 200; wl++) {
    for (int i = 1; i <= n; i++) parent[i] = i;
    for (auto [x, y, w] : edges) {
      if (w >= wl) Union(x, y);
    }
    for (int i = 0; i < k; i++) {
      auto [x, y] = queries[i];
      if (Find(x) == Find(y)) ans[i] = wl;
    }
  }

  for (int i = 0; i < k; i++) cout << ans[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
