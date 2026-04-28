#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000;
ll tree[MAX + 10][MAX + 10];
int n, m;

void add(int x, int y, int val) {
  for (int i = x; i <= n; i += i & -i) for (int j = y; j <= m; j += j & -j) {
    tree[i][j] += val;
  }
}

void solve() {
  int q;
  cin >> n >> m >> q;

  while (q--) {
    int op;
    cin >> op;
    if (op == 1) {
      int xs, ys, xe, ye, val;
      cin >> xs >> ys >> xe >> ye >> val;
      add(xs, ys, val);
      add(xe + 1, ys, -val);
      add(xs, ye + 1, -val);
      add(xe + 1, ye + 1, val);
    }
    else {
      int x, y;
      cin >> x >> y;
      ll res = 0;
      for (int i = x; i > 0; i -= i & -i) for (int j = y; j > 0; j -= j & -j) {
        res += tree[i][j];
      }
      cout << res << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
