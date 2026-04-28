#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int parent[(int)2e2 + 1];

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

  int n, m, c, g;
  cin >> n >> m;

  for (int i = 0; i <= n; i++) parent[i] = i;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> c;
      if (c) Union(i, j);
    }
  }

  bool able = true;
  cin >> c;
  g = Find(c);
  m--;

  while (m--) {
    cin >> c;
    if (Find(c) != g) {
      able = false;
      break;
    }
  }

  cout << (able ? "YES" : "NO") << '\n';
}
