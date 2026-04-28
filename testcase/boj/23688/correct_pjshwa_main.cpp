#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
vector<int> graph[MAX + 1];
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
  int n, m, q;
  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++) parent[i] = i;

  while (m--) {
    for (int i = 1; i <= n; i++) {
      int x;
      cin >> x;
      Union(i, x);
    }
  }

  while (q--) {
    int a, b;
    cin >> a >> b;

    if (Find(a) == Find(b)) cout << "DA\n";
    else cout << "NE\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
