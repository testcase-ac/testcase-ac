#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50, MAXC = 26, INF = 0x3f3f3f3f;
vector<int> P[MAXC + 1];
int dp[MAXC + 1][MAXN];

void solve() {
  string S; cin >> S;
  int N = S.size();
  for (int i = 0; i < N; ++i) {
    int c = S[i] - 'a' + 1;
    P[c].push_back(i);
  }

  memset(dp, 0x3f, sizeof(dp)); dp[0][0] = 0;
  for (int c = 1; c <= 26; ++c) {
    if (P[c].empty()) {
      for (int i = 0; i < N; ++i) dp[c][i] = dp[c - 1][i];
    }
    else {
      // start from ppos, cover the char range, then go to npos
      for (int ppos = 0; ppos < N; ++ppos) for (int npos = 0; npos < N; ++npos) {
        int spos = P[c].front(), epos = P[c].back(), cost = INF;
        cost = min(cost, abs(ppos - spos) + abs(npos - epos) + epos - spos);
        cost = min(cost, abs(ppos - epos) + abs(npos - spos) + epos - spos);
        dp[c][npos] = min(dp[c][npos], dp[c - 1][ppos] + cost);
      }
    }
  }

  int ans = INF;
  for (int i = 0; i < N; ++i) ans = min(ans, dp[MAXC][i]);
  cout << ans + N << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
