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

void solve(int v, int e) {
  ll ans = 0;
  for (int i = 0; i < v; i++) parent[i] = i;

  // Kruskal's algorithm
  vector<tuple<int, int, int>> ta;
  for (int i = 0; i < e; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    ans += c;
    ta.push_back({c, a, b});
  }
  sort(ta.begin(), ta.end());

  for (auto [w, x, y] : ta) {
    if (Find(x) == Find(y)) continue;
    ans -= w;
    Union(x, y);
  }

  cout << ans << '\n';
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  while (1) {
    int v, e;
    cin >> v >> e;
    if (v == 0 && e == 0) break;
    solve(v, e);
  }
}
