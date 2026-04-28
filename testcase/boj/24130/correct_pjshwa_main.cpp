#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXW = 1000, MAXN = 1e4, MOD = 1e7;
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
int W, H, N; string S;

int dp[50][50][50][4];
int rec(int i, int j, int l, int d) {
  if (l == 2) cout << "rec(" << i << ", " << j << ", " << l << ", " << d << ")\n";
  if (dp[i][j][l][d] != -1) return dp[i][j][l][d];
  if (l == N) {
    if (d == 0 && i == 0) return j != W;
    if (d == 3 && j == W) return i != 0;
    return 0;
  }

  int ret = 0, ci = i + dx[d], cj = j + dy[d];
  int nd = S[l] == 'L' ? (d + 3) % 4 : (d + 1) % 4;
  while (ci <= H && cj <= W && ci >= 0 && cj >= 0) {
    ret = (ret + rec(ci, cj, l + 1, nd)) % MOD;
    ci += dx[d], cj += dy[d];
  }
  return dp[i][j][l][d] = ret;
}

void solve() {
  cin >> W >> H >> N >> S;
  memset(dp, -1, sizeof(dp));
  
  int ans = 0;
  for (int d : {0, 3}) ans = (ans + rec(H, 0, 0, d)) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
