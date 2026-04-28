#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 10, MAXV = 1e5, INF = 0x3f3f3f3f;
int a[MAX][MAX], dp[MAXV + 1];

void solve() {
  int n, d, x; cin >> n >> d >> x;
  for (int i = 0; i < d; i++) for (int j = 0; j < n; j++) cin >> a[i][j];

  int ans = x;
  for (int i = 1; i < d; i++) {
    memset(dp, 0, sizeof(dp));
    for (int j = 0; j < n; j++) {
      int val = a[i][j] - a[i - 1][j];
      int prc = a[i - 1][j]; 
      if (val <= 0) continue;

      for (int v = prc; v <= MAXV; v++) {
        dp[v] = max(dp[v], dp[v - prc] + val);
      }
    }
    ans += dp[ans];
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
