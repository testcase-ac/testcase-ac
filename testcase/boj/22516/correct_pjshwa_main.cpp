#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 2000, MAXM = 1e5, INF = 1e18;
ll K[MAXN], S[MAXM + 1], P[MAXM + 1];
ll dp[MAXN + 1][MAXN + 1], N, L;

ll rec(int i, int j) {
  if (dp[i][j] != -1) return dp[i][j];
  if (i == 0 || j == 0) {
    if (i > j) swap(i, j);
    return dp[i][j] = (P[K[j]] - P[K[i] - 1]) / L;
  }

  ll li = min(i, j) - 1, ret = INF;
  ret = min(ret, rec(li, j) + (P[K[i]] - P[K[li] - 1]) / L);
  ret = min(ret, rec(i, li) + (P[K[j]] - P[K[li] - 1]) / L);
  return dp[i][j] = ret;
}

void solve() {
  int M; cin >> N >> M >> L;
  for (int i = 0; i < N; ++i) cin >> K[i];
  sort(K, K + N);
  for (int i = 1; i <= M; ++i) {
    cin >> S[i];
    P[i] = P[i - 1] + S[i];
  }

  memset(dp, -1, sizeof(dp));
  cout << rec(N - 1, N - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
