#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e4;
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
  int N, M; cin >> N >> M;

  iota(parent, parent + N + 1, 0);
  vector<tii> edges;
  while (M--) {
    int ai, bi, ci, di;
    cin >> ai >> bi >> ci >> di;

    if (di) Union(ai, bi);
    else edges.push_back({ci, ai, bi});
  }

  sort(edges.begin(), edges.end(), greater<>());
  int ans = 0;
  for (auto [ci, ai, bi] : edges) {
    if (Find(ai) == Find(bi)) ans += ci;
    else Union(ai, bi);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
