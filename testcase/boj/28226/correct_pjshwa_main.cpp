#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000;
const ld INF = 1e18;
int T[MAX], P[MAX];
int dp[MAX];
bool reachable[MAX][MAX];

// how many points do you need til point i?
int rec(int i) {
  if (i == 0) return 1;
  if (dp[i] != -1) return dp[i];

  int ret = i + 1;
  for (int j = i - 1; j >= 0; --j) {
    if (reachable[j][i]) ret = min(ret, rec(j) + 1);
  }

  return dp[i] = ret;
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> T[i] >> P[i];
  int D; cin >> D;

  for (int i = 0; i < N; ++i) {
    // max and min slope if you want to include all points of i~j, starting from point i
    ld mxs = INF, mns = -INF;

    for (int j = i + 1; j < N; ++j) {
      int xdif = T[j] - T[i], ydif_max = P[j] + D - P[i], ydif_min = P[j] - D - P[i];
      ld slope_max = (ld)ydif_max / xdif, slope_min = (ld)ydif_min / xdif;
      mxs = min(mxs, slope_max); mns = max(mns, slope_min);

      // if the slope is within range, then you can reach j from i
      ld slope = (ld)(P[j] - P[i]) / xdif;
      if (mns <= slope && slope <= mxs) {
        reachable[i][j] = true;
      }
    }
  }

  memset(dp, -1, sizeof(dp));
  cout << rec(N - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
