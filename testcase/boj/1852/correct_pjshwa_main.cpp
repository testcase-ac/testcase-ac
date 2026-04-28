#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 1e5, INF = 1e18;
int A[MAXN + 1][3], N;
ll dp[MAXN + 1][8];

void fill_def(ll val) {
  for (int i = 0; i <= N; ++i) for (int j = 0; j < 8; ++j) dp[i][j] = val;
  dp[1][6] = abs(A[1][1] - A[1][2]);
  dp[1][3] = abs(A[1][0] - A[1][1]);
  dp[1][0] = 0;
}

void solve() {
  cin >> N;
  for (int i = 1; i <= N; ++i) for (int j = 0; j < 3; ++j) cin >> A[i][j];

  // max sum of diffs
  fill_def(-INF);
  for (int i = 2; i <= N; ++i) for (int ps = 0; ps < 8; ++ps) {
    int ns = 0, diff_sum = 0;
    for (int j = 0; j < 3; ++j) {
      if (ps & (1 << j)) continue;
      ns |= 1 << j;
      diff_sum += abs(A[i][j] - A[i - 1][j]);
    }
    dp[i][ns] = max(dp[i][ns], dp[i - 1][ps] + diff_sum);

    if ((ns & 1) == 0 && (ns & 2) == 0) {
      dp[i][ns | 3] = max(dp[i][ns | 3], dp[i - 1][ps] + diff_sum + abs(A[i][0] - A[i][1]));
    }
    if ((ns & 2) == 0 && (ns & 4) == 0) {
      dp[i][ns | 6] = max(dp[i][ns | 6], dp[i - 1][ps] + diff_sum + abs(A[i][1] - A[i][2]));
    }
  }
  cout << dp[N][7] << '\n';

  // min sum of diffs
  fill_def(INF);
  for (int i = 2; i <= N; ++i) for (int ps = 0; ps < 8; ++ps) {
    int ns = 0, diff_sum = 0;
    for (int j = 0; j < 3; ++j) {
      if (ps & (1 << j)) continue;
      ns |= 1 << j;
      diff_sum += abs(A[i][j] - A[i - 1][j]);
    }
    dp[i][ns] = min(dp[i][ns], dp[i - 1][ps] + diff_sum);

    if ((ns & 1) == 0 && (ns & 2) == 0) {
      dp[i][ns | 3] = min(dp[i][ns | 3], dp[i - 1][ps] + diff_sum + abs(A[i][0] - A[i][1]));
    }
    if ((ns & 2) == 0 && (ns & 4) == 0) {
      dp[i][ns | 6] = min(dp[i][ns | 6], dp[i - 1][ps] + diff_sum + abs(A[i][1] - A[i][2]));
    }
  }
  cout << dp[N][7] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
