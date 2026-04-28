#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int parent[MAX + 1], dt[MAX + 1];
set<int> p[MAX + 1];

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
  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    parent[i] = i;
    p[i].clear();
    p[i].insert(i);
  }
  memset(dt, 0, sizeof(dt));

  while (m--) {
    string op;
    cin >> op;
    if (op == "?") {
      int a, b;
      cin >> a >> b;
      if (Find(a) == Find(b)) cout << dt[b] - dt[a] << '\n';
      else cout << "UNKNOWN\n";
    }
    if (op == "!") {
      int a, b, w;
      cin >> a >> b >> w;
      if (Find(a) == Find(b)) continue;
      else {
        int fa = Find(a), fb = Find(b);
        int offset = dt[a] + w - dt[b];

        if (p[fa].size() > p[fb].size()) {
          for (int e : p[fb]) {
            dt[e] += offset;
            p[fa].insert(e);
          }
          p[fb].clear();
          Union(fa, fb);
        }
        else {
          for (int e : p[fa]) {
            dt[e] -= offset;
            p[fb].insert(e);
          }
          p[fa].clear();
          Union(fb, fa);
        }
      }
    }

  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
