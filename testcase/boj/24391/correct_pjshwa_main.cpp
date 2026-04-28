#include <bits/stdc++.h>
using namespace std;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
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

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) parent[i] = i;

  while (m--) {
    int x, y;
    cin >> x >> y;
    Union(x, y);
  }

  int ans = 0, prv;
  cin >> prv;
  for (int i = 2; i <= n; i++) {
    int cur;
    cin >> cur;
    if (Find(cur) != Find(prv)) ans++;
    prv = cur;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
