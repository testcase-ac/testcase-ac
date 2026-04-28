#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000, INF = 0x3f3f3f3f;
char board[MAXN + 1][MAXN + 1];
int dp[MAXN + 1][2];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> board[i];

  vector<tuple<int, int, int>> A;
  for (int i = 1; i <= N; ++i) {
    int ll = N, rr = 0;
    for (int j = 1; j <= N; ++j) {
      if (board[i][j - 1] == '0') continue;
      ll = min(ll, j); rr = max(rr, j);
    }
    if (rr) A.emplace_back(i, ll, rr);
  }
  int Z = A.size();
  if (Z == 0) return cout << 2 * N - 1 << '\n', void();

  memset(dp, 0x3f, sizeof(dp));
  auto& [l, ll, rr] = A[0];
  if (l == 1) dp[0][1] = rr;
  else {
    dp[0][1] = l - 1 + rr;
    dp[0][0] = dp[0][1] + rr - ll;
  }

  for (int i = 1; i < Z; ++i) {
    auto& [pl, pll, prr] = A[i - 1];
    auto& [l, ll, rr] = A[i];

    // pll -> rr -> ll
    if (l > pl + 1 || rr <= pll) {
      int d = l - pl + abs(rr - pll) + rr - ll;
      dp[i][0] = min(dp[i][0], dp[i - 1][0] + d);
    }

    // pll -> ll -> rr
    {
      int d = l - pl + abs(ll - pll) + rr - ll;
      dp[i][1] = min(dp[i][1], dp[i - 1][0] + d);
    }

    // prr -> rr -> ll
    {
      int d = l - pl + abs(rr - prr) + rr - ll;
      dp[i][0] = min(dp[i][0], dp[i - 1][1] + d);
    }

    // prr -> ll -> rr
    if (l > pl + 1 || ll >= prr) {
      int d = l - pl + abs(ll - prr) + rr - ll;
      dp[i][1] = min(dp[i][1], dp[i - 1][1] + d);
    }
  }

  auto& [last_l, last_ll, last_rr] = A[Z - 1]; int ans;
  if (last_l == N) ans = dp[Z - 1][1] + N - last_rr;
  else ans = N - last_l + min(dp[Z - 1][0] + N - last_ll, dp[Z - 1][1] + N - last_rr);

  if (ans >= INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
