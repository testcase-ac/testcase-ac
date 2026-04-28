#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 1000;
int B[MAXV + 1][MAXV + 1];

void solve() {
  int n, m, Q; cin >> n >> m >> Q;

  auto oob = [&](int y, int x) {
    return y < 1 || y > n || x < 1 || x > m;
  };

  int tot = n * m;
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) B[i][j] = 1;

  while (Q--) {
    int op; cin >> op;
    if (op == 1) {
      int dy, dx, y, x; cin >> dy >> dx >> y >> x;
      while (!oob(y, x) && B[y][x]) {
        B[y][x] = 0; --tot;
        y += dy; x += dx;
      }
    }
    if (op == 2) {
      int y, x; cin >> y >> x;
      cout << 1 - B[y][x] << '\n';
    }
    if (op == 3) {
      cout << tot << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
