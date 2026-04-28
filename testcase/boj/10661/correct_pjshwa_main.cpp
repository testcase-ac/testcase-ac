#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
int parent[MAX + 1];

int Find(int x) {
  if (x != parent[x]) parent[x] = Find(parent[x]);
  return parent[x];
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

int n, m;
void solve() {
  vector<tuple<int, int, int>> edges;
  while (m--) {
    int s, t, c; cin >> s >> t >> c;
    edges.emplace_back(c, s, t);
  }
  sort(edges.begin(), edges.end());

  iota(parent, parent + n + 1, 0); int usz = 0;
  for (auto& [c, s, t] : edges) {
    if (Find(s) == Find(t)) continue;

    Union(s, t); usz++;
    if (usz == n / 2) return cout << c << '\n', void();
  }
}

int main() {
  fast_io();

  while (cin >> n >> m) {
    if (n == 0 && m == 0) break;
    solve();
  }
}
