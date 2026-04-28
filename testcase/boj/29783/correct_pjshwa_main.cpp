#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int dp[MAXN][3];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  string S; cin >> S;
  string B = "RPS";

  int N = S.size(), ans = N;
  for (int f = 0; f < 3; ++f) for (int b = 0; b < 3; ++b) {
    if (B[f] == B[b]) continue;

    memset(dp, 0x3f, sizeof(dp));
    dp[0][f] = 0;
    for (int i = 1; i < N; ++i) {
      for (int c = 0; c < 3; ++c) for (int p = 0; p < 3; ++p) {
        if (c == p) continue;
        dp[i][c] = min(dp[i][c], dp[i - 1][p] + (B[c] != S[i]));
      }
    }
    int cnt = (B[f] != S[0]) + dp[N - 1][b];
    ans = min(ans, cnt);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
