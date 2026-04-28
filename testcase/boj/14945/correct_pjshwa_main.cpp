#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100, MOD = 10'007;
int d[MAX + 1][MAX + 1][MAX + 1];
int N;

int r(int i, int x, int y) {
  if (i == N) return 1;
  if (d[i][x][y] != -1) return d[i][x][y];

  int res = 0;
  for (int dx : {0, 1}) for (int dy : {0, 1}) {
    int nx = x + dx, ny = y + dy;
    if (nx == ny || nx > i + 1 || ny > i + 1) continue;
    res = (res + r(i + 1, nx, ny)) % MOD;
  }

  return d[i][x][y] = res;
}

void solve() {
  cin >> N;
  memset(d, -1, sizeof(d));
  cout << r(1, 1, 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
