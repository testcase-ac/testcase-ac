#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int a[100'000], dp[100'000][2];
int main() {
  fast_io();

  int n, ans;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  ans = dp[0][0] = dp[0][1] = a[0];
  for (int i = 1; i < n; i++) {
    dp[i][0] = max(dp[i - 1][0] + a[i], a[i]);
    dp[i][1] = max(dp[i - 1][0], dp[i - 1][1] + a[i]);
    ans = max(ans, max(dp[i][0], dp[i][1]));
  }

  cout << ans << '\n';
}
