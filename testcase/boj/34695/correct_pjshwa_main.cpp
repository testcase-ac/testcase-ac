#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXA = 26, MAXN = 1e5, MOD = 1e9 + 7;
int D[MAXA][MAXA], dp[MAXN][MAXA];

void solve() {
  int K, N; cin >> K >> N;
  for (int i = 0; i < K; ++i) {
    string S; cin >> S;
    D[S[0] - 'a'][S[1] - 'a'] = 1;
  }

  for (int j = 0; j < MAXA; ++j) dp[0][j] = 1;

  int ans = 0;
  for (int i = 1; i < N; ++i) {
    for (int pj = 0; pj < MAXA; ++pj) for (int j = 0; j < MAXA; ++j) {
      if (!D[pj][j]) continue;
      dp[i][j] = (dp[i][j] + dp[i - 1][pj]) % MOD;
    }
    for (int j = 0; j < MAXA; ++j) ans = (ans + dp[i][j]) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
