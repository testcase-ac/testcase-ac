#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
int board[MAX + 1][MAX + 1], d[MAX + 1][MAX + 1];

int w(int sx, int sy, int ex, int ey) {
  if (ey < sy) return 0;

  d[sx][sy] = 1;
  for (int i = sx; i <= ex; i++) {
    for (int j = sy; j <= ey; j++) {
      if (i == sx && j == sy) continue;

      if (board[i][j]) d[i][j] = 0;
      else d[i][j] = d[i - 1][j] + d[i][j - 1];
    }
  }

  return d[ex][ey];
}

void solve() {
  int N, M, A, B;
  cin >> N >> M >> A >> B;

  map<int, set<int>> S;
  while (A--) {
    int x, y;
    cin >> x >> y;
    S[x].insert(y);
  }
  while (B--) {
    int x, y;
    cin >> x >> y;
    board[x][y] = 1;
  }

  int lx = 1, ly = 1, ans = 1;
  for (auto [x, ys] : S) {
    ans *= w(lx, ly, x, *ys.begin());
    lx = x; ly = *ys.rbegin();
  }
  ans *= w(lx, ly, N, M);

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
