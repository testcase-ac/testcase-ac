#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2000;

// dp[i][j] = i-th index, truth value j, minimum number of operations
int dp[MAXN + 1][2];

void solve() {
  int N; cin >> N;
  memset(dp, 0x3f, sizeof(dp));

  string O; cin >> O;
  if (O == "T") dp[0][0] = 1, dp[0][1] = 0;
  else dp[0][0] = 0, dp[0][1] = 1;

  N /= 2;
  for (int i = 1; i <= N; ++i) {
    string op, val; cin >> op >> val;

    for (int lt = 0; lt < 2; ++lt) for (int nt = 0; nt < 2; ++nt) for (int nop = 0; nop < 2; ++nop) {
      int t, cost = 0;
      if (nop == 0) t = (lt & nt);
      else t = (lt | nt);

      cost += ((nop == 0) ^ (op == "&"));
      cost += ((nt == 0) ^ (val == "F"));

      dp[i][t] = min(dp[i][t], dp[i - 1][lt] + cost);
    }
  }

  string R; cin >> R;
  if (R == "T") cout << dp[N][1] << '\n';
  else cout << dp[N][0] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
