#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 6e5, BIAS = 3e5;
int parent[MAX + 1], usz[MAX + 1], G[MAX + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

int inv(int x) {
  return x < BIAS ? x + BIAS : x - BIAS;
}

void solve() {
  int N, Q; cin >> N >> Q;
  iota(parent, parent + MAX + 1, 0);
  fill(usz, usz + MAX + 1, 1);

  int ans = 0;
  auto Union = [&](int x, int y) {
    x = Find(x); y = Find(y);
    if (x == y) return;

    if (G[x]) ans -= usz[x];
    if (G[y]) ans -= usz[y];

    parent[y] = x;
    usz[x] += usz[y];

    G[x] |= G[y] | (Find(x) == Find(inv(x)));
    if (G[x]) ans += usz[x];
  };

  while (Q--) {
    int x, y; cin >> x >> y;
    Union(x, inv(y)); Union(inv(x), y);
    cout << ans / 2 << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
