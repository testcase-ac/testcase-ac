#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5, INF = 0x3f3f3f3f;
int A[MAXN + 1];
pii dp[MAXN + 1][6];

void solve() {
  string S; cin >> S;
  int N = S.size();
  for (int i = 1; i <= N; ++i) cin >> A[i];
  for (int i = 0; i <= N; ++i) {
    for (int j = 0; j < 6; ++j) dp[i][j] = {-INF, -INF};
  }
  dp[0][0] = {0, 0};

  string T = "bessie";
  for (int i = 1; i <= N; ++i) {
    char c = S[i - 1];
    for (int j = 0; j < 6; ++j) {
      auto [pcnt, pcost] = dp[i - 1][j];
      if (j == 0) dp[i][j] = {pcnt, pcost};
      else dp[i][j] = {pcnt, pcost - A[i]};
    }
    for (int j = 0; j < 6; ++j) {
      auto [pcnt, pcost] = dp[i - 1][j];
      if (c == T[j]) {
        int ncnt = pcnt, nj = j + 1;
        if (j == 5) ++ncnt, nj = 0;
        dp[i][nj] = max(dp[i][nj], {ncnt, pcost});
      }
    }
  }

  auto [cnt, cost] = dp[N][0];
  cout << cnt << '\n' << -cost << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
