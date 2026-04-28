#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 300, INF = 0x3f3f3f3f;
int dp[MAXN + 1][MAXN + 1];
int N, M; string S, T;

int rec(int i, int j) {
  if (dp[i][j] != -1) return dp[i][j];
  if (i == N) {
    if (j == M) return dp[i][j] = 0;
    int cost = abs(S.back() - T[j]);
    return dp[i][j] = rec(i, j + 1) + cost;
  }
  else if (j == M) {
    int cost = abs(S[i] - T.back());
    return dp[i][j] = rec(i + 1, j) + cost;
  }

  int ret = INF, cost = abs(S[i] - T[j]);
  ret = min(ret, rec(i + 1, j + 1) + cost);
  ret = min(ret, rec(i + 1, j) + cost);
  ret = min(ret, rec(i, j + 1) + cost);
  return dp[i][j] = ret;
}

void solve() {
  cin >> N >> M >> S >> T;
  memset(dp, -1, sizeof(dp));
  cout << rec(0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
