#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
double dp[7][7][7][MAXN + 1];

int N;
void init() {
  for (int i = 0; i < 7; ++i) for (int j = 0; j < 7; ++j) for (int k = 0; k < 7; ++k) {
    for (int l = 0; l <= N; ++l) dp[i][j][k][l] = -1;
  }
}

int score(int p1, int p2, int p3) {
  if (p1 == p2 && p2 == p3) return 10'000 + p1 * 1'000;
  if (p1 == p2 || p1 == p3) return 1'000 + p1 * 100;
  if (p2 == p3) return 1'000 + p2 * 100;
  return max({p1, p2, p3}) * 100;
}

double rec(int p1, int p2, int p3, int l) {
  if (dp[p1][p2][p3][l] != -1) return dp[p1][p2][p3][l];

  double ret = score(p1, p2, p3);
  if (l < N) {
    double next = 0;
    for (int np = 1; np <= 6; ++np) next += rec(p2, p3, np, l + 1);
    ret = max(ret, next / 6);
  }
  return dp[p1][p2][p3][l] = ret;
}

void solve() {
  cin >> N;

  init();
  double ans = 0;
  for (int p1 = 1; p1 <= 6; ++p1) for (int p2 = 1; p2 <= 6; ++p2) for (int p3 = 1; p3 <= 6; ++p3) {
    ans += rec(p1, p2, p3, 3);
  }
  ans /= 216;
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
