#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2000;
double A[MAXN], dp[MAXN][MAXN];
int N, L, W, H;

double dist(double x1, double y1, double x2, double y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double rec(int i, int r) {
  if (i == N) return 0;
  if (dp[i][r] != -1) return dp[i][r];

  int l = i - r; double ret = 1e18;
  if (l < H) {
    double pos = (double)L * l / (H - 1);
    ret = min(ret, rec(i + 1, r) + dist(A[i], 0, pos, 0));
  }
  if (r < H) {
    double pos = (double)L * r / (H - 1);
    ret = min(ret, rec(i + 1, r + 1) + dist(A[i], 0, pos, W));
  }
  return dp[i][r] = ret;
}

void solve() {
  cin >> N >> L >> W; H = N / 2;
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    fill(dp[i], dp[i] + N, -1);
  }
  sort(A, A + N);

  cout << fixed << setprecision(10) << rec(0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
