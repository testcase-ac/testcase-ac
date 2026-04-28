#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2000, MAXF = 1000, MOD = 1e8;
int dp[MAXN + 1][MAXF];

void solve() {
  int N, F; cin >> N >> F;

  dp[0][0] = 1;
  for (int i = 1; i <= N; ++i) {
    for (int pf = 0; pf < F; ++pf) {
      dp[i][pf] = dp[i - 1][pf];
    }

    int x; cin >> x;
    for (int pf = 0; pf < F; ++pf) {
      int nf = (pf + x) % F;
      dp[i][nf] = (dp[i][nf] + dp[i - 1][pf]) % MOD;
    }
  }

  int ans = (dp[N][0] - 1 + MOD) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
