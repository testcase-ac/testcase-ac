#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N, Q;
  cin >> N >> Q;

  bool e = 0;
  while (Q--) {
    int op, x, y;
    cin >> op >> x >> y;
    if (op == 1) e = !e;
    if (op == 2) {
      int p = (y - x + 1) / 2;
      if (p & 1) e = !e;
    }
    cout << e << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
