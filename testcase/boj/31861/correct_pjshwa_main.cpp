#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, MOD = 1e9 + 7;
int dp[MAXN + 1][26];

void solve() {
  int d, N; cin >> d >> N;

  fill(dp[1], dp[1] + 26, 1);
  for (int i = 2; i <= N; ++i) for (int pc = 0; pc < 26; ++pc) for (int nc = 0; nc < 26; ++nc) {
    if (abs(pc - nc) < d) continue;
    dp[i][nc] = (dp[i][nc] + dp[i - 1][pc]) % MOD;
  }

  int ans = 0;
  for (int c = 0; c < 26; ++c) ans = (ans + dp[N][c]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
