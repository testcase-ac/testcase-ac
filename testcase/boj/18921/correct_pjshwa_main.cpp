#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int parent[MAX + 1], usz[MAX + 1];

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
  vector<tii> edges;
  for (int i = 0; i < n - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    edges.push_back(make_tuple(u, v, w));
  }
  sort(edges.begin(), edges.end(), [](const tii& a, const tii& b) {
    return get<2>(a) > get<2>(b);
  });

  for (int i = 1; i <= n; i++) parent[i] = i, usz[i] = 1;

  ll ans = 0;
  for (auto& [u, v, w] : edges) {
    Union(u, v);
    ans = max(ans, (ll)w * (usz[Find(u)] - 1));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
