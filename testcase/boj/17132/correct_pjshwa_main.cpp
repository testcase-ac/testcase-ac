#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int parent[MAX], usz[MAX];

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
  for (int i = 0; i < n; i++) parent[i] = i, usz[i] = 1;

  vector<tii> edges;
  for (int i = 0; i < n - 1; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    edges.emplace_back(-w, x - 1, y - 1);
  }
  sort(edges.begin(), edges.end());

  ll ans = 0;
  for (auto [w, x, y] : edges) {
    x = Find(x);
    y = Find(y);
    ans += (ll)-w * usz[x] * usz[y];
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
