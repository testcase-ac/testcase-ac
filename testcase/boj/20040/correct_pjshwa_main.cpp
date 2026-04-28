#include <bits/stdc++.h>
using namespace std;

int parent[500'001];

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

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, m, a, b;
  cin >> n >> m;
  for (int i = 0; i < n; i++) parent[i] = i;

  for (int i = 1; i <= m; i++) {
    cin >> a >> b;
    if (Find(a) == Find(b)) {
      cout << i;
      return 0;
    }
    Union(a, b);
  }

  cout << 0;
}
