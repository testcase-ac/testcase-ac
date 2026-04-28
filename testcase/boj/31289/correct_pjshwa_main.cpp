#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 200, INF = 0x3f3f3f3f;
int dp[MAXN + 1][MAXN + 1][MAXN + 1];

int rec(int x, int y, int z) {
  if (x == 0 && y == 0 && z == 0) return 0;
  if (dp[x][y][z] != -1) return dp[x][y][z];

  int xr = (x ^ y ^ z), sm = x + y + z, al = INF;
  if (xr == 0) {
    for (int i = 1; i <= x; ++i) al = min(al, rec(x - i, y, z));
    for (int i = 1; i <= y; ++i) al = min(al, rec(x, y - i, z));
    for (int i = 1; i <= z; ++i) al = min(al, rec(x, y, z - i));
  }
  else {
    if ((x ^ xr) < x) al = min(al, rec(x ^ xr, y, z));
    if ((y ^ xr) < y) al = min(al, rec(x, y ^ xr, z));
    if ((z ^ xr) < z) al = min(al, rec(x, y, z ^ xr));
  }

  return dp[x][y][z] = sm - al;
}

void solve() {
  int x, y, z; cin >> x >> y >> z;

  int asum = rec(x, y, z);
  int bsum = x + y + z - asum;
  cout << asum << "0000 " << bsum << "0000\n";
}

int main() {
  fast_io();

  memset(dp, -1, sizeof(dp));

  int t = 1;
  cin >> t;
  while (t--) solve();
}
