#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500, INF = 1e9 + 7;
int parent[MAX + 1];
int cost[MAX + 1][MAX + 1];

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
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) parent[i] = i;
  for (int i = 1; i <= n; i++) {
    int u, v;
    cin >> u >> v;
    Union(u, v);
  }
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cost[i][j] = cost[j][i] = INF;

  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
    int v, x = Find(i), y = Find(j);
    cin >> v;
    if (x == y) continue;
    cost[x][y] = min(cost[x][y], v);
    cost[y][x] = min(cost[y][x], v);
  }

  set<int> islands;
  for (int i = 1; i <= n; i++) islands.insert(Find(i));

  int ans = INF;
  for (int x : islands) {
    int cur = 0;
    for (int y : islands) {
      if (x != y) cur += cost[x][y];
    }
    ans = min(ans, cur);
  }

  cout << 2 * ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
