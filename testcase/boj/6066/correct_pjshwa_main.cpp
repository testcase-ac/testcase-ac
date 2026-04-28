#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXH = 55000;
int dp[MAXH + 1];

void solve() {
  int N, H; cin >> N >> H;

  memset(dp, 0x3f, sizeof(dp)); dp[0] = 0;
  for (int i = 0; i < N; ++i) {
    int p, c; cin >> p >> c;
    for (int j = p; j <= MAXH; ++j) dp[j] = min(dp[j], dp[j - p] + c);
  }

  int ans = dp[H];
  for (int j = H; j <= MAXH; ++j) ans = min(ans, dp[j]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
