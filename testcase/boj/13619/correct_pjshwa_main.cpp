#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 200;
const double INF = 1e18;
double X[MAXN + 1], Y[MAXN + 1];
double dp[MAXN + 1][MAXN + 1];
int N;

double dist(int i, int j) {
  if (abs(i - j) == 1 || abs(i - j) == N - 1) return 0;
  return sqrt((X[i] - X[j]) * (X[i] - X[j]) + (Y[i] - Y[j]) * (Y[i] - Y[j]));
}

double rec(int l, int r) {
  // cout << "rec(" << l << ", " << r << ")\n";
  if (dp[l][r] != -1) return dp[l][r];

  double ret = INF; int dif = (r - l + N) % N;
  if (dif == 1) return dp[l][r] = 0;

  for (int i = 1; i < dif; i += 2) for (int j = i + 1; j < dif; j += 2) {
    int l2 = (l + i) % N, r2 = (l + j) % N;
    ret = min(ret, rec(l, l2) + rec(l2, r2) + rec(r2, r) + dist(l, r));
  }
  return dp[l][r] = ret;
}

void solve() {
  cin >> N; N *= 2;
  for (int i = 0; i < N; ++i) cin >> X[i] >> Y[i];
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) dp[i][j] = -1;

  double ans = INF;
  for (int i = 0; i < N; ++i) {
    int l = (i + 3) % N, r = i;
    ans = min(ans, rec(l, r));
  }
  cout << fixed << setprecision(4) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
