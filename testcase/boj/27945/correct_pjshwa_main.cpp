#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
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

  vector<tii> E;
  while (M--) {
    int u, v, t; cin >> u >> v >> t;
    E.emplace_back(t, u, v);
  }
  sort(E.begin(), E.end());

  int ans = 1;
  for (auto& [t, u, v] : E) {
    if (Find(u) != Find(v) && ans == t) {
      Union(u, v);
      ans++;
    }
    else break;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
