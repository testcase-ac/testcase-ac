#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e5;
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

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) parent[i] = i;
  for (int i = 0; i < n - 2; i++) {
    int a, b;
    cin >> a >> b;
    Union(a, b);
  }

  for (int i = 2; i <= n; i++) if (Find(1) != Find(i)) {
    cout << "1 " << i << '\n';
    break;
  }
}
