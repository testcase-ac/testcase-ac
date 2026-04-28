#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
int dp[MAXN + 1];

void solve() {
  memset(dp, 0x3f, sizeof(dp)); dp[0] = 0;
  for (int i = 1; i <= MAXN; ++i) {
    int j = 1, cost = 1;
    while (j <= i) {
      dp[i] = min(dp[i], dp[i - j] + cost);
      j = j * 2 + 1;
      ++cost;
    }
    cout << "dp[" << i << "] = " << dp[i] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
