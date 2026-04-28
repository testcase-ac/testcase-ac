#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5, MOD = 1e9 + 7;
int A[MAXN + 10], dp[MAXN + 10];
set<int> R[MAXN + 10];

void solve() {
  int N, s, e; cin >> N;
  for (int i = 1; i <= N; ++i) {
    cin >> A[i];

    s = i - 1, e = i + A[i];
    if (e <= N) R[e].insert(s);

    s = i - A[i] - 1, e = i;
    if (s >= 0) R[e].insert(s);
  }

  dp[0] = 1;
  for (int e = 1; e <= N; ++e) {
    for (int s : R[e]) dp[e] = (dp[e] + dp[s]) % MOD;
  }
  cout << dp[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
