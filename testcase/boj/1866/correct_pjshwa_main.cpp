#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3000;
int A[MAXN + 1], P[MAXN + 1], V[MAXN + 1][MAXN + 1], dp[MAXN + 1];

void solve() {
  int N, S, T; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];
  sort(A + 1, A + N + 1);
  for (int i = 1; i <= N; ++i) P[i] = A[i] + P[i - 1];
  cin >> S >> T;

  // helicopter ranges
  for (int l = 1; l <= N; ++l) for (int r = l + 1; r <= N; ++r) {
    int m = (l + r) / 2;
    int lcnt = m - l + 1, rcnt = r - m;
    int lsum = P[m] - P[l - 1], rsum = P[r] - P[m];
    V[l][r] = A[m] * lcnt - lsum + rsum - A[m] * rcnt;
  }

  for (int i = 1; i <= N; ++i) {
    dp[i] = dp[i - 1] + A[i] * S;
    for (int p = i; p >= 1; --p) dp[i] = min(dp[i], dp[p - 1] + S * V[p][i] + T);
  }
  cout << dp[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
