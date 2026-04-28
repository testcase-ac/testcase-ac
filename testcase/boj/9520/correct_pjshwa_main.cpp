#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 1500, INF = 1e18;
ll N, A[MAXN + 1][MAXN + 1], dp[MAXN + 1][MAXN + 1];

ll rec(int l, int r) {
  if (l == N || r == N) return 0;
  if (dp[l][r] != -1) return dp[l][r];

  ll next = max(l, r) + 1, ret = INF;
  ret = min(ret, rec(next, r) + A[l][next]);
  ret = min(ret, rec(l, next) + A[r][next]);
  return dp[l][r] = ret;
}

void solve() {
  cin >> N;
  for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) cin >> A[i][j];

  memset(dp, -1, sizeof(dp));
  cout << rec(1, 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
