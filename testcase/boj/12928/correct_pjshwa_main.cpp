#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50, MAXT = 100, MAXV = 1000;
bool dp[2][MAXT + 1][MAXV + 1];

void solve() {
  int N, S; cin >> N >> S;
  int T = 2 * N - 2;

  dp[0][0][0] = true;
  for (int i = 1; i <= N; ++i) {
    int x = i % 2;
    memset(dp[x], 0, sizeof(dp[x]));

    for (int t = 1; t < N; ++t) {
      int add = t * (t - 1) / 2;
      for (int pt = 0; pt + t <= T; ++pt) for (int v = 0; v + add <= S; ++v) {
        dp[x][pt + t][v + add] |= dp[1 - x][pt][v];
      }
    }
  }

  cout << dp[N % 2][T][S] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
