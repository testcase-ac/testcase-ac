#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 400;
int A[MAXN], dp[MAXN][MAXN];

int rec(int i, int j) {
  if (dp[i][j] != -1) return dp[i][j];
  if (i == j) return dp[i][j] = A[i];

  int ret = 0;
  for (int k = i; k < j; ++k) {
    int lhs = rec(i, k), rhs = rec(k + 1, j);
    if (lhs == rhs && lhs != 0) ret = max(ret, 2 * lhs);
  }

  int rk = j;
  for (int lk = i; lk < j; ++lk) {
    int lhs = rec(i, lk);
    while (rk > lk && rec(rk, j) < lhs) --rk;
    if (rk <= lk) break;

    int rhs = rec(rk, j);
    if (lhs == rhs && lhs != 0) {
      if (lk + 1 <= rk - 1) {
        int mid = rec(lk + 1, rk - 1);
        if (mid > 0) ret = max(ret, 2 * lhs + mid);
      }
    }
  }
  return dp[i][j] = ret;
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];

  memset(dp, -1, sizeof(dp)); int ans = 0;
  for (int i = 0; i < N; ++i) for (int j = i; j < N; ++j) ans = max(ans, rec(i, j));
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
