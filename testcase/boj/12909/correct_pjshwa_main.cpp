#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 51;
int S[MAXN + 1];
int dp[MAXN + 1][MAXN + 1];

int rec(int e, int l) {
  if (dp[e][l] != -1) return dp[e][l];
  if (e == 0) return dp[e][l] = S[1] * l;

  int ret = 0;
  for (int c = 1; c <= e; ++c) {
    ret = max(ret, rec(e - c, l + c - 1) + S[c + 1]);
  }
  return dp[e][l] = ret;
}

void solve() {
  int N; cin >> N;
  for (int i = 1; i < N; ++i) cin >> S[i];

  memset(dp, -1, sizeof(dp));

  int ret = 0;
  for (int e = 1; e < N; ++e) ret = max(ret, rec(N - e - 1, e) + S[e]);
  cout << ret << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
