#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5, INF = 0x3f3f3f3f;
int P[4][MAXN + 1], dp[MAXN + 1][4][4];

bool is_valid(int i, int s) {
  if (P[1][i] == 0 && (s & 1)) return false;
  if (P[1][i] == 1 && !(s & 1)) return false;
  if (P[3][i] == 0 && (s & 2)) return false;
  if (P[3][i] == 1 && !(s & 2)) return false;
  return true;
}

void solve() {
  int N, M; cin >> N >> M;

  memset(P, -1, sizeof(P));
  while (M--) {
    int xi, yi; cin >> xi >> yi;
    cin >> P[xi][yi];
  }

  memset(dp, 0x3f, sizeof(dp));
  for (int s0 = 1; s0 < 4; ++s0) {
    if (is_valid(1, s0)) dp[1][0][s0] = __builtin_popcount(s0);
  }
  for (int i = 2; i <= N; ++i) {
    for (int s0 = 1; s0 < 4; ++s0) {
      if (!is_valid(i, s0)) continue;
      for (int s1 = 0; s1 < 4; ++s1) for (int s2 = 0; s2 < 4; ++s2) {
        if (!(s0 & 1) && !(s1 & 1) && !(s2 & 1)) continue;
        if (!(s0 & 2) && !(s1 & 2) && !(s2 & 2)) continue;
        dp[i][s1][s0] = min(dp[i][s1][s0], dp[i - 1][s2][s1] + __builtin_popcount(s0));
      }
    }
  }

  int ans = INF;
  for (int s0 = 0; s0 < 4; ++s0) for (int s1 = 0; s1 < 4; ++s1) {
    if ((s0 | s1) != 3) continue;
    ans = min(ans, dp[N][s1][s0]);
  }
  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
