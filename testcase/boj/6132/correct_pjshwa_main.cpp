#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5, MAXH = 100;
int A[MAXN]; ll dp[2][MAXH + 1];

void solve() {
  int N, C; cin >> N >> C;

  int mH = 0;
  for (int i = 0; i < N; ++i) cin >> A[i], mH = max(mH, A[i]);

  for (int h = A[0]; h <= mH; ++h) dp[0][h] = (h - A[0]) * (h - A[0]);
  for (int i = 1; i < N; ++i) {
    fill(dp[i % 2], dp[i % 2] + mH + 1, LLONG_MAX);
    for (int ph = A[i - 1]; ph <= mH; ++ph) for (int nh = A[i]; nh <= mH; ++nh) {
      int cost = C * abs(nh - ph) + (nh - A[i]) * (nh - A[i]);
      dp[i % 2][nh] = min(dp[i % 2][nh], dp[(i - 1) % 2][ph] + cost);
    }
  }

  ll ans = LLONG_MAX;
  for (int h = A[N - 1]; h <= mH; ++h) ans = min(ans, dp[(N - 1) % 2][h]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
