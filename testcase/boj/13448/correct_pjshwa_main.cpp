#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50, MAXT = 1e5;
ll N, T, M[MAXN], P[MAXN], R[MAXN];
ll dp[MAXN][MAXT + 1];

ll rec(int i, int t) {
  if (i == N) return 0;
  if (dp[i][t] != -1) return dp[i][t];

  ll ret = rec(i + 1, t);
  if (t + R[i] <= T) {
    ll score = M[i] - (t + R[i]) * P[i];
    if (score > 0) ret = max(ret, rec(i + 1, t + R[i]) + score);
  }
  return dp[i][t] = ret;
}

void solve() {
  cin >> N >> T;
  for (int i = 0; i < N; ++i) cin >> M[i];
  for (int i = 0; i < N; ++i) cin >> P[i];
  for (int i = 0; i < N; ++i) cin >> R[i];

  vector<tuple<ll, ll, ll>> A;
  for (int i = 0; i < N; ++i) A.emplace_back(M[i], P[i], R[i]);
  sort(A.begin(), A.end(), [](auto &a, auto &b) {
    auto [am, ap, ar] = a; auto [bm, bp, br] = b;
    return ar * bp < br * ap;
  });
  for (int i = 0; i < N; ++i) tie(M[i], P[i], R[i]) = A[i];

  memset(dp, -1, sizeof(dp));
  cout << rec(0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
