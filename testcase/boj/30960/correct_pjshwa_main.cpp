#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
int A[MAXN];
ll dp[MAXN][2];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    dp[i][0] = dp[i][1] = 1e18;
  }

  sort(A, A + N);
  dp[1][0] = A[1] - A[0];
  dp[2][1] = A[2] - A[0];
  for (int i = 3; i < N; ++i) {
    dp[i][0] = min(dp[i][0], dp[i - 2][0] + A[i] - A[i - 1]);
    dp[i][1] = min(dp[i][1], dp[i - 2][1] + A[i] - A[i - 1]);
    dp[i][1] = min(dp[i][1], dp[i - 3][0] + A[i] - A[i - 2]);
  }
  cout << dp[N - 1][1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
