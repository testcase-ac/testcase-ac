#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 200;
string S; int N, dp[MAXN][MAXN];

int rec(int l, int r) {
  if (l > r) return 0;
  if (l == r) return 1;
  if (dp[l][r] != -1) return dp[l][r];

  int ret = rec(l + 1, r) + 1;
  for (int len = 1; len <= r - l; ++len) {
    int rep = 1, val = rec(l, l + len - 1);
    while (1) {
      ret = min(ret, rec(l + len * rep, r) + 2 + val + (int)to_string(rep).size());
      int ok = 1;
      for (int i = 0; i < len; ++i) ok &= S[l + i] == S[l + i + len * rep];
      if (!ok) break;
      ++rep;
    }
  }
  return dp[l][r] = ret;
}

void solve() {
  cin >> S; N = S.size();
  memset(dp, -1, sizeof dp);
  cout << rec(0, N - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
