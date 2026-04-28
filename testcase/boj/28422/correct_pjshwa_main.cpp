#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, INF = 0x3f3f3f3f;
int A[MAX + 1], dp[MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; i++) cin >> A[i];

  if (N == 1) return cout << "0\n", void();

  dp[1] = -INF;
  for (int i = 2; i <= N; i++) {
    dp[i] = dp[i - 2] + __builtin_popcount(A[i] ^ A[i - 1]);
    if (i >= 3) dp[i] = max(dp[i], dp[i - 3] + __builtin_popcount(A[i] ^ A[i - 1] ^ A[i - 2]));
  }
  cout << dp[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
