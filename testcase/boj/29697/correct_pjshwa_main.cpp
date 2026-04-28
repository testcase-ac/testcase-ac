#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 1e5, MAXQ = 630, INF = 1e18;
int C[MAXN + 10], M_R[MAXN + 10][MAXQ], P;
ll dp[MAXN + 10];

ll C2(ll x) {
  return x * (x + 1) / 2;
}

ll f(int l, int r, int i) {
  ll ret = C2(i - l + 1) + C2(r - i + 1) - 1;
  // cout << "l = " << l << ", r = " << r << ", i = " << i << ", ret = " << ret << '\n';
  return ret;
}

ll g(int l, int r) {
  ll ret = INF;
  for (int j = l; j <= r; ++j) {
    ll cost = f(l, r, j);
    if (cost <= P) ret = min(ret, (ll)C[j]);
  }
  return ret;
}

void solve() {
  int N; cin >> N >> P;
  for (int i = 1; i <= N; ++i) cin >> C[i];
  for (int l = 1; l <= N; ++l) {
    M_R[l][0] = C[l];
    for (int a = 1; l + a <= N; ++a) {
      int r = l + a, m = (l + r) / 2;
      if (f(l, r, m) > P) break;
      M_R[l][a] = min(M_R[l][a - 1], C[r]);
    }
  }

  // where is the "edge" point, if len of range is N?
  vector<int> E(N + 1); int i = 1;
  for (int l = 1; l <= N; ++l) {
    while (i <= N && f(1, l, i) > P) ++i;
    E[l] = i - 1;
  }

  fill(dp + 1, dp + N + 1, INF);
  for (int r = 1; r <= N; ++r) {
    for (int l = r; l >= 1; --l) {

      // calculate range for cost
      int len = r - l + 1;
      int offset = E[len];
      if (offset == N) break;

      int lo = l + offset, hi = r - offset;
      int cost = M_R[lo][hi - lo];

      dp[r] = min(dp[r], dp[l - 1] + cost);
    }
  }

  cout << dp[N] << '\n';

  // // backtrack
  // for (int i = N; i > 0; ) {
  //   for (int j = 0; j < i; ++j) {
  //     if (dp[i] == dp[j] + g(j + 1, i)) {
  //       cout << "j: " << j << ", i: " << i << '\n';
  //       i = j;
  //       break;
  //     }
  //   }
  // }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
