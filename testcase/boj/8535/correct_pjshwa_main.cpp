#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int parent[2 * MAX + 1];

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

int idx = 0;
map<int, int> v2i;

int t(int v) {
  if (v2i.count(v)) return v2i[v];
  else {
    v2i[v] = ++idx;
    return idx;
  }
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= 2 * MAX; i++) parent[i] = i;

  for (int i = 1; i <= n; i++) {
    int x, y, s;
    cin >> x >> y >> s;
    x--;

    x = t(x), y = t(y);
    if (s) Union(x, y + MAX), Union(y, x + MAX);
    else Union(x, y), Union(x + MAX, y + MAX);

    if (Find(x) == Find(x + MAX) || Find(y) == Find(y + MAX)) return cout << i - 1 << '\n', void();
  }

  cout << n << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
