#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, MOD = 1e9 + 7;
int dp[MAX + 1][10][2][3];

void solve() {
  int N; cin >> N;

  for (int c = 0; c < 10; ++c) {
    dp[1][c][0][0] = 1;
    dp[1][c][1][0] = 1;
  }
  for (int i = 2; i <= N; ++i) for (int c = 0; c < 10; ++c) for (int pc : {c - 1, c + 1}) {
    if (pc < 0 || pc > 9) continue;

    int nj = c > pc;
    for (int pj = 0; pj < 2; ++pj) for (int ps = 0; ps < 3; ++ps) {
      int ns = nj == pj ? ps + 1 : 1;
      if (ns < 3) dp[i][c][nj][ns] = (dp[i][c][nj][ns] + dp[i - 1][pc][pj][ps]) % MOD;
    }
  }

  ll ans = 0, inv2 = 500000004;
  for (int c = 0; c < 10; ++c) for (int j = 0; j < 2; ++j) for (int s = 0; s < 3; ++s) {
    ans = (ans + dp[N][c][j][s]) % MOD;
  }
  ans = (ans * inv2) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
