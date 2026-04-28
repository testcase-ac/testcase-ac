#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, INF = 0x3f3f3f3f;
int d[MAX + 1][MAX + 1][MAX + 1][40];

int r(int a, int b, int c, int t) {
  if (a == 0 && b == 0 && c == 0) return 0;
  if (d[a][b][c][t] != -INF) return d[a][b][c][t];

  int ret = -INF;
  if (a) ret = max(ret, min(a, t) - r(max(0, a - t), b, c, t + 1));
  if (b) ret = max(ret, min(b, t) - r(a, max(0, b - t), c, t + 1));
  if (c) ret = max(ret, min(c, t) - r(a, b, max(0, c - t), t + 1));

  return d[a][b][c][t] = ret;
}

void solve() {
  int a, b, c;
  cin >> a >> b >> c;

  for (int i = 0; i <= a; ++i) {
    for (int j = 0; j <= b; ++j) {
      for (int k = 0; k <= c; ++k) {
        for (int l = 0; l < 40; ++l) {
          d[i][j][k][l] = -INF;
        }
      }
    }
  }

  int res = r(a, b, c, 1);
  if (res > 0) cout << "F\n";
  else if (res == 0) cout << "D\n";
  else cout << "S\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
