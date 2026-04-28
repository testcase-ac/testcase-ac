#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
int P[MAXN + 1], B[MAXN + 1], dp[MAXN + 1][MAXN + 1];

void solve() {
  int N, M, K; cin >> N >> M >> K;
  for (int i = 1; i <= N; ++i) cin >> P[i];
  for (int i = 0; i <= M; ++i) cin >> B[i];

  memset(dp, -1, sizeof(dp)); dp[0][0] = 0;
  for (int i = 1; i <= N; ++i) {
    for (int nv = P[i]; nv <= M; ++nv) for (int pk = 0; pk <= K; ++pk) {
      int nk = pk + nv - P[i];
      if (nk > K || dp[i - 1][pk] == -1) continue;
      dp[i][nk] = max(dp[i][nk], dp[i - 1][pk] + B[nv]);
    }
  }
  cout << *max_element(dp[N], dp[N] + K + 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
