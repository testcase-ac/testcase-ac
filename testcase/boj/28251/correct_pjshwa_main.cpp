#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
ll parent[MAX + 1], usz1[MAX + 1], usz2[MAX + 1];

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

  if (x == y) return;

  parent[y] = x;
  usz1[x] += usz1[y];
  usz2[x] += usz2[y];
}

void solve() {
  int N, Q; cin >> N >> Q;
  iota(parent, parent + N + 1, 0);
  for (int i = 1; i <= N; i++) {
    int x; cin >> x;
    usz1[i] = x; usz2[i] = x * x;
  }

  while (Q--) {
    int u, v; cin >> u >> v;
    Union(u, v);

    int g = Find(u);
    cout << (usz1[g] * usz1[g] - usz2[g]) / 2 << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
