#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int parent[MAX], usz[MAX];
bool u[MAX];

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
  int n, m, q;
  cin >> n >> m >> q;

  for (int i = 0; i < n; i++) parent[i] = i, usz[i] = 1;

  vector<pii> edges;
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    edges.emplace_back(x - 1, y - 1);
  }

  vector<int> qs;
  while (q--) {
    int x;
    cin >> x;
    u[x - 1] = 1;
    qs.push_back(x - 1);
  }

  for (int i = 0; i < m; i++) {
    if (!u[i]) {
      auto [x, y] = edges[i];
      Union(x, y);
    }
  }

  ll ans = 0;
  reverse(qs.begin(), qs.end());

  for (auto &i: qs) {
    auto [x, y] = edges[i];
    if (Find(x) == Find(y)) continue;

    ll sx = usz[Find(x)], sy = usz[Find(y)];
    ans += sx * sy;
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
