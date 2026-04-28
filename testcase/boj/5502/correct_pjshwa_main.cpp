#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000;
int dp[MAXN][MAXN];
string S;
int rec(int s, int e) {
  if (s >= e) return 0;
  if (dp[s][e] != -1) return dp[s][e];

  int ret;
  if (S[s] == S[e]) ret = rec(s + 1, e - 1);
  else ret = min(rec(s + 1, e), rec(s, e - 1)) + 1;
  return dp[s][e] = ret;
}

void solve() {
  int N; cin >> N >> S;
  memset(dp, -1, sizeof(dp));
  cout << rec(0, N - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
