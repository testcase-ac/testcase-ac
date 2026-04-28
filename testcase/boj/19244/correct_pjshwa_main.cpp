#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500, INF = 0x3f3f3f3f;
string S; int N, dp[MAXN][MAXN];

bool is_match(char a, char b) {
  if (a == '(' && b == ')') return true;
  if (a == '[' && b == ']') return true;
  if (a == '{' && b == '}') return true;
  if (a == '*' && b == ')') return true;
  if (a == '*' && b == ']') return true;
  if (a == '*' && b == '}') return true;
  if (a == '(' && b == '*') return true;
  if (a == '[' && b == '*') return true;
  if (a == '{' && b == '*') return true;
  if (a == '*' && b == '*') return true;
  return false;
}

void solve() {
  cin >> S; N = S.size();
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) dp[i][j] = 0;
  for (int i = 0; i < N; ++i) dp[i][i] = 1;
  for (int d = 1; d < N; ++d) for (int l = 0; l + d < N; ++l) {
    int r = l + d;
    dp[l][r] = is_match(S[l], S[r]) ? dp[l + 1][r - 1] : INF;
    dp[l][r] = min(dp[l][r], dp[l + 1][r] + 1);
    dp[l][r] = min(dp[l][r], dp[l][r - 1] + 1);
    for (int k = l; k < r; k++) {
      int lv = dp[l][k], rv = dp[k + 1][r];
      if (lv == INF || rv == INF) continue;
      dp[l][r] = min(dp[l][r], lv + rv);
    }
  }
  cout << dp[0][N - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
