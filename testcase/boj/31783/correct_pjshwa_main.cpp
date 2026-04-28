#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3e5;
int A[MAXN + 1], B[MAXN + 1], H[MAXN + 1];
ll dp[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> H[i], H[i] = -H[i];
  for (int i = 2; i <= N; ++i) cin >> A[i];

  for (int i = 2; i <= N; ++i) {
    int x; cin >> x;

    // dp[i] = max scores in range [1, i]
    auto it = upper_bound(H + 1, H + i, H[i] - x);
    if (it == H + 1) dp[i] = dp[i - 1];
    else dp[i] = max(dp[i - 1], dp[it - H - 1] + A[i]);
  }
  cout << dp[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
