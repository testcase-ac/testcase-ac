#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
int parent[MAX];

int Find(int x) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

void solve() {
  int N, M; cin >> N >> M;

  iota(parent, parent + N, 0);
  vector<tuple<int, int, int, int>> edges;
  while (M--) {
    int x, y, z, w; cin >> x >> y >> z >> w;
    edges.emplace_back(z, w, x, y);
  }
  sort(edges.begin(), edges.end());

  int uc = 0, C[10]{}; ll wgt = 0;
  for (auto [z, w, x, y] : edges) {
    x = Find(x), y = Find(y);
    if (x == y) continue;

    C[z]++; wgt += w;
    Union(x, y); uc++;
  }

  if (uc == N - 1) {
    for (int d = 1; d <= 9; d++) {
      while (C[d]) cout << d, C[d]--;
    }
    cout << ' ' << wgt << '\n';
  }
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
