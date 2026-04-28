#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 30, MAXK = 500, MOD = 1e9 + 7;
int C[MAXN + 1][MAXN + 1], dp[MAXN + 1][MAXK + 1];

int rec(int n, int k) {
  if (n > k) return 0;
  if (n <= 1) return n == k;
  if (dp[n][k] != -1) return dp[n][k];

  ll tot = k - n, ret = 0;
  for (int s = 1; s <= n; ++s) for (int t = 0; t <= tot; ++t) {
    ll cur = C[n - 1][s - 1];
    cur = (cur * rec(s - 1, t)) % MOD;
    cur = (cur * rec(n - s, tot - t)) % MOD;
    ret = (ret + cur) % MOD;
  }
  return dp[n][k] = ret;
}

void solve() {
  C[0][0] = 1;
  for (int i = 1; i <= MAXN; ++i) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
  }
  memset(dp, -1, sizeof(dp));

  int N, K; cin >> N >> K;
  if (K > MAXK) cout << "0\n";
  else cout << rec(N, K) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
