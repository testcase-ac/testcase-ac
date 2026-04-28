#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
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

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= 2 * MAX; i++) parent[i] = i;

  for (int i = 0; i < m; i++) {
    int x, y; string s;
    cin >> x >> y >> s;

    if (s == "T") Union(x, y), Union(x + MAX, y + MAX);
    else Union(x, y + MAX), Union(x + MAX, y);

    if (Find(x) == Find(x + MAX) || Find(y) == Find(y + MAX)) {
      cout << i << '\n';
      return;
    }
  }

  cout << m << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
