#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 400;
int N, K; double dp[MAXN + 1][MAXN + 1];

// number of heads, number of trials
double rec(int h, int k) {
  if (k == K) return h;
  if (dp[h][k] >= 0) return dp[h][k];

  int t = N - h; double ret = 0;
  if (h) {
    double prob = 0.5 * rec(h - 1, k + 1) + 0.5 * rec(h, k + 1);
    ret = max(ret, prob);
  }
  if (t) {
    double prob = 0.5 * rec(h + 1, k + 1) + 0.5 * rec(h, k + 1);
    ret = max(ret, prob);
  }
  return dp[h][k] = ret;
}

void solve() {
  cin >> N >> K;
  for (int i = 0; i <= N; ++i) for (int j = 0; j < K; ++j) dp[i][j] = -1;
  cout << fixed << setprecision(10) << rec(0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
