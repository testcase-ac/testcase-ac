#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, MOD = 1e9 + 7;
int A[MAX], B[MAX];
ll dp[MAX][2], N;

// currently choosing i-th problem
// b: whether B[i-1] has been used once
ll rec(int i, int b) {
  if (i == N) return 1;
  if (dp[i][b] != -1) return dp[i][b];

  ll mul = i == 0 ? A[i] : A[i] + B[i - 1] - b;
  ll ret = mul * rec(i + 1, 0) % MOD;
  ret = (ret + B[i] * rec(i + 1, 1)) % MOD;
  return dp[i][b] = ret;
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < N - 1; ++i) cin >> B[i];
  
  memset(dp, -1, sizeof(dp));
  cout << rec(0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
