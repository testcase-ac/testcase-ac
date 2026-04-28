#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
int dp[2][MAXN + 1], N, K;

void solve() {
  cin >> N >> K;

  for (int i = 1; i <= K; ++i) dp[0][i] = dp[1][i] = i;
  for (int i = K + 1; i <= N; ++i) {
    for (int p = 0; p < 2; ++p) {
      int sta = p ? 1 : 2;
      int len = K - sta + 1;
      int res = (dp[1 - p][i - sta] - dp[1 - p][i - K - 1]) < len;
      dp[p][i] = dp[p][i - 1] + res;
    }
  }

  int res = dp[0][N] - dp[0][N - 1];
  if (res) cout << "A and B win\n";
  else cout << "C win\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
