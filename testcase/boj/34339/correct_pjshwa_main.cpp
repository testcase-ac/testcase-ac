#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5, MAXV = 100;
int A[MAXN + 1], P[MAXV + 1][MAXN + 1], dp[MAXV + 1];

bool is_valid(int l, int r) {
  vector<int> values;
  for (int v = 1; v <= MAXV; ++v) {
    int cnt = min(P[v][r] - P[v][l - 1], MAXV / v);
    while (cnt--) values.push_back(v);
  }

  memset(dp, 0, sizeof dp); dp[0] = 1;
  for (int x : values) {
    for (int v = MAXV; v >= x; --v) {
      dp[v] = dp[v] || dp[v - x];
    }
    if (dp[MAXV]) return true;
  }
  return false;
}

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];
  for (int v = 1; v <= MAXV; ++v) for (int i = 1; i <= N; ++i) {
    P[v][i] = P[v][i - 1] + (A[i] == v);
  }

  ll ans = 0, pr = 1;
  for (int i = 1; i <= N; ++i) {
    int l = pr, r = N + 1;
    while (l < r) {
      int m = (l + r) / 2;
      if (is_valid(i, m)) r = m;
      else l = m + 1;
    }
    // cout << "i = " << i << ", r = " << r << '\n';
    ans += N - r + 1;
    pr = r;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
