#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 10, INF = 1e18;
ll dp[2][1 << MAXN], A[MAXN], B[MAXN], X[MAXN], M[MAXN];

void solve() {
  ll N, R, oscore, xscore, ps, add; cin >> N >> R;
  for (int i = 0; i < N; ++i) cin >> A[i] >> B[i] >> X[i] >> M[i];

  for (int r = 1; r <= R; ++r) {

    // initialize
    fill(dp[r & 1], dp[r & 1] + (1 << N), -INF);

    for (int i = 0; i < N; ++i) {
      X[i] = (A[i] * X[i] + B[i]) % M[i];
    }

    // TO BE state
    for (int s = 0; s < (1 << N); ++s) {
      oscore = xscore = 0;
      for (int i = 0; i < N; ++i) {
        if (s & (1 << i)) oscore += X[i];
        else xscore += X[i];
      }

      // card # to flip
      for (int i = 0; i < N; ++i) {
        ps = s ^ (1 << i);
        if (s & (1 << i)) add = oscore;
        else add = xscore;
        dp[r & 1][s] = max(dp[r & 1][s], dp[(r - 1) & 1][ps] + add);
      }

    }
  }

  ll ans = 0;
  for (int s = 0; s < (1 << N); ++s) ans = max(ans, dp[R & 1][s]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
