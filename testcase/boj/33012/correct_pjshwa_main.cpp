#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
ll A[MAXN], dp[MAXN];

void solve() {
  int N, ai = 0; cin >> N;
  for (int i = 0; i < N; i += 4) {
    for (int e : {N - i - 1, N - i, N - i - 2, N - i - 3}) {
      if (e > 0) A[ai++] = e;
    }
  }

  dp[0] = A[0]; dp[1] = A[1];
  ll ans = max(dp[0], dp[1]);
  for (int i = 2; i < N; ++i) {
    dp[i] = max(dp[i - 1], dp[i - 2] + A[i]);
    ans = max(ans, dp[i]);
  }

  for (int i = 0; i < N; ++i) cout << A[i] << ' ';
  cout << '\n' << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
