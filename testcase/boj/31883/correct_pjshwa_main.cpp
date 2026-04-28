#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int A[MAXN + 1], B[MAXN + 1], C[MAXN + 1], D[MAXN + 1];
ll dp[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) {
    cin >> A[i] >> B[i] >> C[i] >> D[i];
  }

  for (int i = 1; i <= N; ++i) {
    int rem = dp[i - 1] % (C[i] + D[i]), extra = A[i];
    if (rem >= C[i]) extra += C[i] + D[i] - rem;
    dp[i] = dp[i - 1] + min(extra, B[i]);
  }
  cout << dp[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
