#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N, S; cin >> N >> S;

  vector<pii> A;
  A.emplace_back(0, 0);
  for (int i = 1; i <= N; ++i) {
    int h, c; cin >> h >> c;
    A.emplace_back(h, c);
  }
  sort(A.begin(), A.end());

  vector<ll> dp(N + 1);
  for (int i = 1; i <= N; ++i) {
    auto& [h, c] = A[i];
    auto it = upper_bound(A.begin(), A.begin() + i, make_pair(h - S, INF));
    if (it == A.begin()) dp[i] = c;
    else {
      int j = it - A.begin() - 1;
      dp[i] = dp[j] + c;
    }
    dp[i] = max(dp[i], dp[i - 1]);
  }
  cout << dp[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
