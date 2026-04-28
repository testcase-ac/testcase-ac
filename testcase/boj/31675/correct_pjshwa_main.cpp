#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 1e5, INF = 1e18;
int A[MAXN + 1];
ll dp[MAXN + 1];

void solve() {
  int N; cin >> N;
  if (N == 1) return cout << "0\n", void();

  ll sum = 0;
  for (int i = 1; i <= N; ++i) cin >> A[i], sum += A[i];

  fill(dp, dp + N + 1, INF);
  dp[0] = 0; dp[1] = A[1]; dp[2] = A[2]; dp[3] = A[1] + A[3];
  for (int i = 4; i <= N; ++i) {
    for (int l = 2; l <= 3; ++l) dp[i] = min(dp[i], dp[i - l] + A[i]);
  }

  cout << sum - min(dp[N - 1], dp[N]) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
