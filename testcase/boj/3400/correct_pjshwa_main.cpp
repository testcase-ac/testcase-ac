#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 40;
ll dp[MAXN + 1][MAXN + 1], N, D;

ll rec(int i, int u) {
  if (dp[i][u] != -1) return dp[i][u];
  if (i == 0) return dp[i][u] = u == 0;

  ll ret = 0;
  if (u < D) ret += rec(i - 1, u + 1);
  if (u > 0) ret += rec(i - 1, u - 1);
  return dp[i][u] = ret;
}

ll upto(int n, int d) {
  memset(dp, -1, sizeof(dp));
  N = n, D = d;
  return rec(N, 0);
}

void solve() {
  int n, d; cin >> n >> d;
  cout << upto(n, d) - upto(n, d - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
