#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, INF = 0x3f3f3f3f;
int A[MAX + 10], N;
int dp[MAX + 10][MAX + 10];

int rec(int l, int r) {
  if (l + 1 == r) return 0;
  if (dp[l][r] != -1) return dp[l][r];

  int ret = INF;
  for (int p = l + 1; p < r; ++p) {
    int cost = A[r] - A[l] - 2 + rec(l, p) + rec(p, r);
    ret = min(ret, cost);
  }
  return dp[l][r] = ret;
}

void solve() {
  int L; cin >> L >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];
  sort(A + 1, A + N + 1);
  A[0] = 0, A[N + 1] = L + 1;

  memset(dp, -1, sizeof(dp));
  cout << rec(0, N + 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
