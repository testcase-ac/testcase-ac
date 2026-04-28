#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXS = 27, MAXN = 20;
int dp[MAXS][MAXN + 1][MAXN + 1][MAXN + 1][3];
int F[3];

int rec(int s, int x, int y, int z, int p) {
  if (x == 0 && y == 0 && z == 0) return (p + 2) % 3;
  if (dp[s][x][y][z][p] != -1) return dp[s][x][y][z][p];

  bool ok1 = false;
  for (int l = 1; l <= x; ++l) ok1 |= (rec(s, x - l, y, z, (p + 1) % 3) == p);
  for (int l = 1; l <= y; ++l) ok1 |= (rec(s, x, y - l, z, (p + 1) % 3) == p);
  for (int l = 1; l <= z; ++l) ok1 |= (rec(s, x, y, z - l, (p + 1) % 3) == p);
  if (ok1) return dp[s][x][y][z][p] = p;

  bool ok2 = false;
  for (int l = 1; l <= x; ++l) ok2 |= (rec(s, x - l, y, z, (p + 1) % 3) == F[p]);
  for (int l = 1; l <= y; ++l) ok2 |= (rec(s, x, y - l, z, (p + 1) % 3) == F[p]);
  for (int l = 1; l <= z; ++l) ok2 |= (rec(s, x, y, z - l, (p + 1) % 3) == F[p]);
  if (ok2) return dp[s][x][y][z][p] = F[p];

  return dp[s][x][y][z][p] = (3 ^ p ^ F[p]);
}

void solve() {
  int x, y, z; cin >> x >> y >> z >> F[0] >> F[1] >> F[2];
  --F[0], --F[1], --F[2];

  int s = 9 * F[0] + 3 * F[1] + F[2];
  int ret = rec(s, x, y, z, 0);
  for (int l = 1; l <= x; ++l) {
    if (rec(s, x - l, y, z, 1) != ret) continue;
    cout << "1 " << l << '\n';
    return;
  }
  for (int l = 1; l <= y; ++l) {
    if (rec(s, x, y - l, z, 1) != ret) continue;
    cout << "2 " << l << '\n';
    return;
  }
  for (int l = 1; l <= z; ++l) {
    if (rec(s, x, y, z - l, 1) != ret) continue;
    cout << "3 " << l << '\n';
    return;
  }
}

int main() {
  fast_io();
  memset(dp, -1, sizeof(dp));

  int t = 1;
  cin >> t;
  while (t--) solve();
}
