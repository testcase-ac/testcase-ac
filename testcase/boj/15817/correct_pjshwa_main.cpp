#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, MAXV = 1e4;
int dp[MAXN + 1][MAXV + 1];

void solve() {
  int N, T; cin >> N >> T;

  dp[0][0] = 1;
  for (int i = 1; i <= N; ++i) {
    int l, c; cin >> l >> c;
    for (int j = 0; j <= c; ++j) {
      for (int w = T; w >= l * j; --w) dp[i][w] += dp[i - 1][w - l * j];
    }
  }
  cout << dp[N][T] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
