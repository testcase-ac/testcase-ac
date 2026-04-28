#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, MAXH = 1e5, MOD = 1e9 + 7;
int A[MAXN + 1], dp[MAXH + 1];

void solve() {
  int N, H; cin >> N >> H;
  for (int i = 1; i <= N; ++i) cin >> A[i];

  dp[0] = 1;
  for (int w = 0; w <= H; ++w) {
    for (int i = 1; i <= N; ++i) {
      int nw = w + A[i];
      if (nw <= H) dp[nw] = (dp[nw] + dp[w]) % MOD;
    }
  }
  cout << dp[H] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
