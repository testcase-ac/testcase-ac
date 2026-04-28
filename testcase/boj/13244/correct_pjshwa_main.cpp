#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
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
  int n, m; cin >> n >> m;

  iota(parent, parent + n + 1, 0);
  for (int i = 0; i < m; i++) {
    int x, y; cin >> x >> y;
    Union(x, y);
  }

  set<int> U;
  for (int i = 1; i <= n; i++) U.insert(Find(i));

  if (m == n - 1 && U.size() == 1) cout << "tree\n";
  else cout << "graph\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
