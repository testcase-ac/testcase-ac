#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int degree[200001], parent[200001];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);

    // Path compression
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

  int n, m, a, b;
  cin >> n >> m;

  for (int i = 1; i <= n; i++) parent[i] = i;

  while (m--) {
    cin >> a >> b;
    degree[a]++;
    degree[b]++;
    Union(a, b);
  }

  map<int, int> o;
  for (int i = 1; i <= n; i++) {
    if (!degree[i]) continue;

    b = Find(i);
    if (!o.count(b)) o[b] = 0;
    if (degree[i] & 1) o[b]++;
  }

  int ans = 0;
  for (auto el : o) ans += max(1, (el.second - 1) / 2 + 1);
  cout << ans << '\n';
}
