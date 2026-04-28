#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
ll dp[MAXN + 1];

void solve() {
  int N, M, R; cin >> N >> M >> R;

  vector<tuple<int, int, ll>> A;
  for (int i = 0; i < M; ++i) {
    int s, e, f; cin >> s >> e >> f;
    A.emplace_back(s, e, f);
  }
  sort(A.begin(), A.end(), [](auto &a, auto &b) {
    return get<1>(a) < get<1>(b);
  });

  int ai = 0;
  for (int i = 1; i <= N; ++i) {
    while (ai < M && get<1>(A[ai]) == i) {
      auto [s, e, f] = A[ai];
      if (s >= R) dp[e] = max(dp[e], dp[s - R] + f);
      else dp[e] = max(dp[e], f);
      ++ai;
    }
    dp[i] = max(dp[i], dp[i - 1]);
  }

  cout << dp[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
