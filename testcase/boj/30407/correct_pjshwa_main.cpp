#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 18, MAXD = 70, INF = 0x3f3f3f3f;
int dp[MAXN][MAXD + 1][2][2];
int A[MAXN], N, K;

// i: i-th skill is being used
// d: chunbae current distance
// ur: whether skill skip is used
// uo: whether skill skip switch is on
int rec(int i, int d, int ur, int uo) {
  if (i >= N) return 0;
  if (dp[i][d][ur][uo] != -1) return dp[i][d][ur][uo];

  int ret = INF, dam = max(0, A[i] - d);

  // skip this skill
  if (uo == 1) {
    ret = min(ret, rec(i + 1, d + K, ur, 0));
    return dp[i][d][ur][uo] = ret;
  }

  // use 웅크리기
  ret = min(ret, rec(i + 1, d, ur, uo) + dam / 2);

  // use 네발로 걷기
  ret = min(ret, rec(i + 1, d + K, ur, uo) + max(0, A[i] - d - K));

  // use 깜짝 놀라게 하기
  if (ur == 0) {
    ret = min(ret, rec(i + 1, d, 1, 1) + dam);
  }

  return dp[i][d][ur][uo] = ret;
}

void solve() {
  int H, D; cin >> N >> H >> D >> K;
  for (int i = 0; i < N; i++) cin >> A[i];

  memset(dp, -1, sizeof(dp));
  int ans = H - rec(0, D, 0, 0);
  if (ans <= 0) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
