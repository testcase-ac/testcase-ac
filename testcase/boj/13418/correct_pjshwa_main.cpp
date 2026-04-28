#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
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

  // Kruskal's algorithm
  vector<tuple<int, int, int>> ta;
  for (int i = 0; i < m + 1; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    ta.push_back({c ^ 1, a, b});
  }

  sort(ta.begin(), ta.end());
  for (int i = 0; i <= n; i++) parent[i] = i;

  ll mw = 0;
  for (auto [w, x, y] : ta) {
    if (Find(x) == Find(y)) continue;
    mw += w;
    Union(x, y);
  }

  sort(ta.begin(), ta.end(), [](auto a, auto b) {
    return get<0>(a) > get<0>(b);
  });
  for (int i = 0; i <= n; i++) parent[i] = i;

  ll xw = 0;
  for (auto [w, x, y] : ta) {
    if (Find(x) == Find(y)) continue;
    xw += w;
    Union(x, y);
  }

  cout << xw * xw - mw * mw << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
