#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, MAXV = 1e5;
int A[MAXN + 10];
bool dp[2][MAXV + 1];

void solve() {
  int N, C, ans = 0; cin >> N >> C;
  for (int i = 1; i <= N; ++i) cin >> A[i], ans += A[i];
  sort(A + 1, A + N + 1); A[N + 1] = MAXV + 1;

  dp[0][0] = true;
  for (int i = 1; i <= N; ++i) {
    int w = A[i], x = (i & 1);
    for (int j = 0; j <= C; ++j) dp[x][j] = dp[x ^ 1][j];
    for (int j = w; j <= C; ++j) {
      dp[x][j] |= dp[x ^ 1][j - w];
      if (dp[x][j] && C - j < A[i + 1]) ans = min(ans, j);
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
