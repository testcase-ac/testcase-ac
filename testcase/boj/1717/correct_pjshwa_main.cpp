#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int parent[(int)1e6 + 1];

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

  int n, m, op, a, b;
  cin >> n >> m;

  for (int i = 0; i <= n; i++) parent[i] = i;

  while (m--) {
    cin >> op >> a >> b;
    if (op == 0) Union(a, b);
    else {
      if (Find(a) == Find(b)) cout << "YES\n";
      else cout << "NO\n";
    }
  }
}
