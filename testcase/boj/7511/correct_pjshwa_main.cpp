#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int parent[MAX];
int tc;

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
  int n, m, q;
  cin >> n >> m;
  for (int i = 0; i < n; i++) parent[i] = i;
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    Union(a, b);
  }

  cin >> q;
  while (q--) {
    int a, b;
    cin >> a >> b;
    if (Find(a) == Find(b)) cout << "1\n";
    else cout << "0\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cout << "Scenario " << i << ":\n";
    solve();
    if (i != t) cout << "\n";
  }
}
