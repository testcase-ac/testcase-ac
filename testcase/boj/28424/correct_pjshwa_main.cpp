#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int A[MAX + 10], M[MAX + 10], L[MAX + 10], parent[MAX + 10];

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

  if (x != y) {
    parent[y] = x;
    L[x] = max(L[x], L[y]);
  }
}

void solve() {
  int N, Q; cin >> N >> Q;
  for (int i = 1; i <= N; i++) cin >> M[i], A[i] = M[i];

  iota(parent, parent + N + 10, 0);

  // First non-zero index
  iota(L, L + N + 10, 0);

  while (Q--) {
    int op; cin >> op;
    if (op == 1) {
      int i, x; cin >> i >> x;
      for (int g = L[Find(i)]; g <= N; g = L[Find(g + 1)]) {
        if (M[g] >= x) {
          M[g] -= x;
          break;
        }
        else {
          x -= M[g];
          M[g] = 0;
          Union(g, g + 1);
        }
      }
    }
    if (op == 2) {
      int i; cin >> i;
      cout << A[i] - M[i] << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
