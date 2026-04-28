#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, MAXV = 10000, INF = 0x3f3f3f3f;
int D[MAXN], T[MAXN][MAXN];
bool adds[MAXV + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> D[i];

  int msum = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < D[i]; ++j) cin >> T[i][j];
    sort(T[i], T[i] + D[i]);
    msum += T[i][0];
  }
  if (msum > M) return cout << "-1\n", void();

  vector<vector<bool>> P(N, vector<bool>(M + 1));

  int base = 0;
  for (int i = 0; i < N; ++i) {
    vector<vector<bool>> dp(D[i], vector<bool>(M + 1));

    dp[0][0] = dp[0][T[i][0]] = true;
    for (int j = 1; j < D[i]; ++j) {
      for (int k = 0; k <= M; ++k) dp[j][k] = dp[j - 1][k];
      for (int k = T[i][j]; k <= M; ++k) {
        dp[j][k] = (dp[j][k] || dp[j - 1][k - T[i][j]]);
      }
    }

    int minx = -1;
    for (int j = 1; j <= M; ++j) {
      if (dp[D[i] - 1][j] && minx == -1) minx = j;
    }
    base += minx;

    for (int j = 1; j <= M; ++j) {
      if (dp[D[i] - 1][j]) adds[j - minx] = true;
    }
  }

  // TODO: adds knapsack

  int ans = 0;
  for (int j = 0; base + j <= M; ++j) {
    if (adds[j]) ans = max(ans, base + j);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
