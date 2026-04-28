#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 4e6;
int parent[MAX + 1], a[MAX + 1];

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
  int n, m, k, x;
  cin >> n >> m >> k;

  for (int i = 1; i <= n; i++) parent[i] = i;
  for (int i = 0; i < m; i++) cin >> a[i];
  sort(a, a + m);

  while (k--) {
    cin >> x;
    int r = Find(upper_bound(a, a + m, x) - a);
    cout << a[r] << '\n';
    Union(r + 1, r);
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
