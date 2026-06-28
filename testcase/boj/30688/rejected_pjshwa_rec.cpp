#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
int dp[2][MAXN + 1], N, K;

int rec(int p, int v) {
  if (v <= K) return 1;
  if (dp[p][v] != -1) return dp[p][v];

  int ret = 0, sta = p ? 1 : 2;
  for (int d = sta; d <= K; ++d) {
    ret |= !rec(p ^ 1, v - d);
  }
  return dp[p][v] = ret;
}

void solve() {
  cin >> N >> K;

  memset(dp, -1, sizeof(dp));
  if (rec(0, N)) cout << "A and B win\n";
  else cout << "C win\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
