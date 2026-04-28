#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
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
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) parent[i] = i;

  // Kruskal's algorithm
  vector<tuple<int, int, int>> ta;
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    ta.push_back(make_tuple(c, a, b));
  }
  sort(ta.begin(), ta.end());

  ll ans = 0, uc = 0;
  for (auto [w, x, y] : ta) {
    if (Find(x) == Find(y)) ans += w;
    else uc++, Union(x, y);
  }

  if (uc == n - 1) cout << ans << '\n';
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
