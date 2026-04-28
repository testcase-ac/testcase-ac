#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int parent[MAXN + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

void solve() {
  int N, M, Q; cin >> N >> M >> Q;
  iota(parent, parent + N + 1, 0);

  while (M--) {
    int u, v; cin >> u >> v;
    Union(u, v);
  }
  while (Q--) {
    int u, v; cin >> u >> v;
    cout << (Find(u) == Find(v) ? 'Y' : 'N') << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
