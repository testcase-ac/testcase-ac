#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 2e5;
int parent[MAX];

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
  int v, e;
  cin >> v >> e;
  vector<bool> s(v);
  for (int i = 0; i < v; i++) {
    string x;
    cin >> x;
    s[i] = x[0] == 'M';
  }

  for (int i = 0; i < v; i++) parent[i] = i;

  // Kruskal's algorithm
  vector<tuple<int, int, int>> ta;
  for (int i = 0; i < e; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    if (s[a - 1] == s[b - 1]) continue;
    ta.push_back({c, a - 1, b - 1});
  }
  sort(ta.begin(), ta.end());

  ll ans = 0;
  int uc = 0;
  for (auto [w, x, y] : ta) {
    if (Find(x) == Find(y)) continue;
    ans += w;
    uc++;
    Union(x, y);
  }

  if (uc == v - 1) cout << ans << '\n';
  else cout << "-1\n";
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
