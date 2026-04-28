#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX], dp[MAX];

int x(int v, int d) {
  return v * 500 + d;
}

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> a[i];

  for (int diff = -100; diff <= 100; diff++) dp[x(a[0], diff)] = 1;
  for (int i = 1; i < N; i++) {
    for (int diff = -100; diff <= 100; diff++) {
      if (a[i] <= diff) continue;

      dp[x(a[i], diff)] = max(
        dp[x(a[i], diff)],
        dp[x(a[i] - diff, diff)] + 1
      );
    }

    for (int diff = -100; diff <= 100; diff++) {
      dp[x(a[i], diff)] = max(dp[x(a[i], diff)], 1);
    }
  }

  cout << *max_element(dp, dp + MAX) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
