#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXL = 1000, MAXN = 30;
int A[MAXN + 1], dp[MAXL + 1][MAXL + 1];

void solve() {
  int L, N; cin >> L >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];

  memset(dp, 0x3f, sizeof(dp)); dp[0][0] = 0;
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
