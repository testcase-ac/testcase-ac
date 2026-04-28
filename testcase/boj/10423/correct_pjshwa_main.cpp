#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 1e3;
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

int main() {
  int n, m, k, x;
  cin >> n >> m >> k;
  for (int i = 0; i <= n; i++) parent[i] = i;
  for (int i = 0; i < k; i++) cin >> x, Union(0, x);

  // Kruskal's algorithm
  vector<tuple<int, int, int>> ta;
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    ta.push_back({w, u, v});
  }
  sort(ta.begin(), ta.end());

  ll ans = 0;
  for (auto [w, x, y] : ta) {
    if (Find(x) == Find(y)) continue;
    ans += w;
    Union(x, y);
  }

  cout << ans << '\n';
}
