#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, INF = 0x3f3f3f3f;
int C[MAXN + 1];
double P[MAXN + 1], dp[MAXN + 1][MAXN + 1];

void solve() {
  int n, w; cin >> n >> w;

  double sum = 0;
  for (int i = 1; i <= n; ++i) cin >> C[i], sum += C[i];
  sort(C + 1, C + n + 1, greater<int>());
  for (int i = 1; i <= n; ++i) P[i] = P[i - 1] + C[i];
  for (int i = 1; i <= n; ++i) P[i] /= sum;

  for (int i = 0; i <= n; ++i) for (int j = 0; j <= w; ++j) dp[i][j] = INF;
  dp[0][0] = 0;

  for (int ci = 1; ci <= n; ++ci) for (int j = 1; j <= w; ++j) {
    for (int k = 0; k < ci; ++k) {
      dp[ci][j] = min(dp[ci][j], dp[k][j - 1] + (P[ci] - P[k]) * ci);
    }
  }
  cout << fixed << setprecision(4) << dp[n][w] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
