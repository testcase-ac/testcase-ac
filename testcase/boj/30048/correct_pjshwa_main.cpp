#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500, MAXE = 500, MOD = 1e9 + 7;
ll dp[MAXN + 1][MAXE + 1];

ll f(int l, int e) {
  if (e == 0) return dp[l][e];
  else return (dp[l][e] - dp[l][e - 1] + MOD) % MOD;
}

void solve() {
  int N, E; cin >> N >> E;

  fill(dp[1], dp[1] + MAXE + 1, 1);
  for (int l = 2; l <= N; ++l) {
    for (int e = 0; e <= MAXE; ++e) {
      // g()
      dp[l][e] = e == 0 ? 0 : f(l - 1, e - 1);

      // f()
      for (int llen = 1; llen < l - 1; ++llen) {
        int rlen = l - llen - 1;

        // left side evals to e
        {
          ll lval = f(llen, e);
          ll rval = (dp[rlen][MAXE] - dp[rlen][e] + MOD) % MOD;
          dp[l][e] = (dp[l][e] + lval * rval) % MOD;
        }

        // right side evals to e
        {
          ll lval = (dp[llen][MAXE] - dp[llen][e] + MOD) % MOD;
          ll rval = f(rlen, e);
          dp[l][e] = (dp[l][e] + lval * rval) % MOD;
        }

        // both sides eval to e
        {
          ll lval = f(llen, e);
          ll rval = f(rlen, e);
          dp[l][e] = (dp[l][e] + lval * rval) % MOD;
        }
      }
    }

    for (int e = 1; e <= MAXE; ++e) {
      dp[l][e] = (dp[l][e] + dp[l][e - 1]) % MOD;
    }
  }

  cout << f(N, E) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
