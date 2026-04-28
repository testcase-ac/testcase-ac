#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int dp[MAXN];

void solve() {
  string S; cin >> S;
  int N = S.size(), ans = 0;
  for (int i = 0; i < N; ++i) {
    dp[i] = 1;
    for (int j = i - 1; j >= 0; j -= 2) {
      if (S[i] == S[j]) dp[i] = max(dp[i], dp[j] + 1);
    }
    ans = max(ans, dp[i]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
