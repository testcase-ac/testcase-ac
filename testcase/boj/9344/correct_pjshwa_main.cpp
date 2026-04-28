#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
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
  int n, m, p, q;
  cin >> n >> m >> p >> q;

  for (int i = 1; i <= n; i++) parent[i] = i;
  int dw;

  // Kruskal's algorithm
  vector<tuple<int, int, int>> ta;
  for (int i = 0, a, b, c; i < m; i++) {
    cin >> a >> b >> c;
    if (a == p && b == q) dw = c;
    if (a == q && b == p) dw = c;
    ta.push_back({c, a, b});
  }
  sort(ta.begin(), ta.end());

  ll anor = 0;
  for (auto [w, x, y] : ta) {
    if (Find(x) == Find(y)) continue;
    anor += w;
    Union(x, y);
  }

  for (int i = 1; i <= n; i++) parent[i] = i;
  Union(p, q);
  ll ainc = dw;
  for (auto [w, x, y] : ta) {
    if (Find(x) == Find(y)) continue;
    ainc += w;
    Union(x, y);
  }

  if (anor == ainc) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
