#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 30000;
int parent[MAX + 1], usz[MAX + 1], U[MAX + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    U[x] += U[parent[x]];
    return parent[x] = p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x == y) return;

  parent[y] = x;
  U[y] += usz[x];
  usz[x] += usz[y];
}

void solve() {
  int N = MAX, P; cin >> P;
  iota(parent, parent + N + 1, 0);
  fill(usz, usz + N + 1, 1);
  while (P--) {
    string op; cin >> op;
    if (op == "M") {
      int x, y; cin >> x >> y;
      Union(x, y);
    }
    else {
      int x; cin >> x;
      cout << usz[Find(x)] - U[x] - 1 << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
