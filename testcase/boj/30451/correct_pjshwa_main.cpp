#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000;
int X[MAXN], Y[MAXN], V[MAXN], W[MAXN];
ll dp[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> X[i] >> Y[i];
  for (int i = 0; i < N; ++i) cin >> V[i] >> W[i];

  vector<tuple<int, int, int, int>> A;
  for (int i = 0; i < N; ++i) {
    if (X[i] + Y[i] > W[i]) continue;
    A.emplace_back(X[i], Y[i], V[i], W[i]);
  }
  sort(A.begin(), A.end(), [](auto &a, auto &b) {
    auto [xi, yi, vi, wi] = a; auto [xj, yj, vj, wj] = b;
    if (wi == wj) return vi > vj;
    return wi < wj;
  });
  N = A.size();

  ll ans = 0;
  for (int i = 0; i < N; ++i) {
    auto [xi, yi, vi, wi] = A[i];
    ll si = max(vi, xi + yi);
    dp[i] = max(dp[i], wi - si);

    for (int j = 0; j < i; ++j) {
      auto [xj, yj, vj, wj] = A[j];
      int mj = abs(xj - xi) + abs(yj - yi);
      ll si = max(vi, wj + mj);
      dp[i] = max(dp[i], dp[j] + wi - si);
    }
    ans = max(ans, dp[i]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
