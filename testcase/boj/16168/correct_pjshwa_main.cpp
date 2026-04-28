#include <bits/stdc++.h>
using namespace std;

int degree[(int)3e3];
int parent[(int)3e3];

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

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

  int v, e, va, vb, odds = 0;
  cin >> v >> e;

  memset(degree, 0, sizeof(degree));
  for (int i = 0; i < v; i++) parent[i] = i;
  for (int i = 0; i < e; i++) {
    cin >> va >> vb;
    degree[va - 1]++;
    degree[vb - 1]++;
    Union(va - 1, vb - 1);
  }

  // Make sure all vertices belong to one graph
  for (int i = 0; i < v; i++) {
    if (Find(i) != Find(0)) {
      cout << "NO\n";
      return 0;
    }
  }

  for (int i = 0; i < v; i++) {
    if (degree[i] & 1) odds++;
  }

  // Euler circuit / path
  if (odds == 0 || odds == 2) cout << "YES\n";
  else cout << "NO\n";
}
