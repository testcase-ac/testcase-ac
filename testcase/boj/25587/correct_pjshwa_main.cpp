#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int parent[MAX + 1], usz[MAX + 1], wsz[MAX + 1], psz[MAX + 1];

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
  usz[x] += usz[y];
  wsz[x] += wsz[y];
  psz[x] += psz[y];
}

void solve() {
  int N, Q;
  cin >> N >> Q;
  for (int i = 1; i <= N; i++) parent[i] = i, usz[i] = 1;
  for (int i = 1; i <= N; i++) cin >> wsz[i];
  for (int i = 1; i <= N; i++) cin >> psz[i];

  int cur = 0;
  for (int i = 1; i <= N; i++) cur += (psz[i] > wsz[i]);

  while (Q--) {
    int op;
    cin >> op;
    if (op == 1) {
      int x, y;
      cin >> x >> y;
      x = Find(x);
      y = Find(y);
      if (x == y) continue;

      if (psz[x] > wsz[x]) cur -= usz[x];
      if (psz[y] > wsz[y]) cur -= usz[y];
      Union(x, y);
      if (psz[x] > wsz[x]) cur += usz[x];
    }
    if (op == 2) cout << cur << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
