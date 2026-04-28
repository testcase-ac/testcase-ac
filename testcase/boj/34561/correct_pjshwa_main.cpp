#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3e5;
int parent[MAXN + 1], G[MAXN + 1], R[MAXN + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

void solve() {
  int N; cin >> N;
  iota(parent, parent + MAXN + 1, 0);
  iota(R, R + MAXN + 1, 0);
  for (int i = 1; i <= N; ++i) cin >> G[i];

  int M; cin >> M;
  while (M--) {
    int op; cin >> op;
    if (op == 1) {
      int x, y; cin >> x >> y;
      Union(x, y);
      R[Find(x)] = y;
    } else {
      int z; cin >> z;
      cout << R[Find(G[z])] << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
