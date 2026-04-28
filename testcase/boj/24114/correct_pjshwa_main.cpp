#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 150'000, MAXL = 20;
int dp[MAXN];

void solve() {
  int N; string S; cin >> N >> S;
  int Z = S.size();

  unordered_set<string> U;
  for (int i = 0; i < N; ++i) {
    string T; cin >> T;
    U.insert(T);
  }

  memset(dp, 0x3f, sizeof(dp)); string cur = "";
  for (int j = 0; j < MAXL; ++j) {
    if (j >= Z) break;
    cur += S[j];
    if (U.count(cur)) dp[j] = 1;
  }

  for (int i = 0; i < Z; ++i) {
    string cur = ""; int mval = 0x3f3f3f3f;
    for (int j = 0; j < MAXL; ++j) {
      if (i + j >= Z) break;
      cur += S[i + j];
      if (U.count(cur)) dp[i + j] = min(dp[i + j], mval + 1);
      mval = min(mval, dp[i + j]);
    }
  }

  cout << dp[Z - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
