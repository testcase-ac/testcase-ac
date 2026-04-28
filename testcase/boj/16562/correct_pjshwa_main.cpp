#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
int parent[MAX + 1];
pii a[MAX + 1];

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
  fast_io();

  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) cin >> a[i].second;
  for (int i = 1; i <= n; i++) parent[i] = i;

  int v, w;
  for (int i = 1; i <= m; i++) {
    cin >> v >> w;
    Union(v, w);
  }
  for (int i = 1; i <= n; i++) a[i].first = Find(i);

  sort(a + 1, a + n + 1);
  int li = 0;
  long long price = 0;
  for (int i = 1; i <= n; i++) {
    if (li != a[i].first) {
      li = a[i].first;
      price += a[i].second;
    }
  }

  if (price <= k) cout << price;
  else cout << "Oh no";
}
