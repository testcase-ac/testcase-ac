#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 200, MOD = 9901;
int dp[MAXN + 1][MAXN + 1];

int rec(int v, int h) {
  if (dp[v][h] != -1) return dp[v][h];
  if (v == 1 && h == 1) return 1;
  if (v == 1 || h == 1) return 0;

  // Case where no children
  int ret = 0;
  for (int lv = 1; lv < v - 1; ++lv) {
    int rv = v - 1 - lv;

    // Left child has height h - 1
    for (int rh = 1; rh < h; ++rh) {
      ret = (ret + rec(lv, h - 1) * rec(rv, rh)) % MOD;
    }
    
    // Right child has height h - 1
    for (int lh = 1; lh < h; ++lh) {
      ret = (ret + rec(lv, lh) * rec(rv, h - 1)) % MOD;
    }

    int both = rec(lv, h - 1) * rec(rv, h - 1) % MOD;
    ret = (ret - both + MOD) % MOD;
  }
  return dp[v][h] = ret;
}

void solve() {
  int N, K; cin >> N >> K;

  memset(dp, -1, sizeof(dp));
  cout << rec(N, K) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
