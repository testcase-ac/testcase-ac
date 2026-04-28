#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int parent[(int)1e2 + 1];

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

  int n, m, a, b, cnt = 0;
  cin >> n >> m;

  for (int i = 0; i <= n; i++) parent[i] = i;

  while (m--) {
    cin >> a >> b;
    Union(a, b);
  }

  for (int i = 2; i <= n; i++) {
    if (Find(i) == Find(1)) cnt++;
  }
  cout << cnt << '\n';
}
