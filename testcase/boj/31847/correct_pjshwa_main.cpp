#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000;
int dp[MAXN][MAXN];

void solve() {
  int N, Q; string S; cin >> N >> S >> Q;

  for (int d = 1; d < N; d += 2) {
    for (int l = 0; l < N; ++l) {
      int r = l + d;
      if (r >= N) break;
      dp[l][r] = dp[l + 1][r - 1] + (S[l] == S[r]);
    }
  }

  for (int d = 1; d < N; ++d) {
    for (int l = 0; l < N; ++l) {
      int r = l + d;
      if (r >= N) break;
      dp[l][r] = max({dp[l][r], dp[l + 1][r], dp[l][r - 1]});
    }
  }
  
  while (Q--) {
    int l, r; cin >> l >> r;
    cout << dp[l - 1][r - 1] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
