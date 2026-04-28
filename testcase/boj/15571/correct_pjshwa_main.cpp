#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e3, MAXM = 1e6, MOD = 1999;
int dp1[MAXN + 1], dp2[MAXM + 1];

void solve() {
  int N, M; cin >> N >> M;

  dp1[0] = 1;
  for (int i = 1; i <= N; ++i) for (int j = 1; j <= i; ++j) {
    dp1[i] = (dp1[i] + dp1[i - j]) % MOD;
  }

  dp2[0] = 1;
  for (int i = 1; i <= M; ++i) {
    if (i >= N) {
      dp2[i] = (dp2[i - 1] - dp2[i - N] + MOD) % MOD;
      if (i == N) dp2[i] = (dp2[i] + dp1[N]) % MOD;
      else dp2[i] = (dp2[i] + (dp2[i - N] - dp2[i - N - 1]) * dp1[N]) % MOD;
    }
    else dp2[i] = dp2[i - 1];
    dp2[i] = (dp2[i] + dp2[i - 1]) % MOD;
  }

  int ans = (dp2[M] - dp2[M - 1] + MOD) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
