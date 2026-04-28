#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000, INF = 2e9 + 1;
int A[MAX + 1], B[MAX + 1];
int dp[MAX + 1][MAX + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= N; i++) cin >> A[i], A[i]--;
  for (int i = 1; i <= M; i++) cin >> B[i], B[i]--;

  for (int i = 0; i <= N; i++) for (int j = 0; j <= M; j++) {
    if (i == 0 && j == 0) continue;
    dp[i][j] = INF;
  }

  for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) {
    dp[i][j] = min({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]}) + A[i] * B[j];
  }
  cout << dp[N][M] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
