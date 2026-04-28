#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
int dp[MAX + 1][MAX + 1][2][3], K;

int rec(int i, int j, int p, int a) {
  // cout << "i: " << i << ", j: " << j << ", p: " << p << ", a: " << a << "\n";

  if (dp[i][j][p][a] != INF + 1) return dp[i][j][p][a];
  if (i == 0 && j == 0) return dp[i][j][p][a] = K * (p == 0 ? 1 : -1);

  int ret = p == 0 ? -INF : INF;

  if (p == 0) {
    // should take at least one
    if (a == 0) {
      if (i) ret = max(ret, rec(i - 1, j, p, 1) + 1);
      if (j) ret = max(ret, rec(i, j - 1, p, 2) + 1);
    }
    // can take from first pillar or switch turn
    if (a == 1) {
      if (i) ret = max(ret, rec(i - 1, j, p, 1) + 1);
      ret = max(ret, rec(i, j, p ^ 1, 0));
    }
    // can take from second pillar or switch turn
    if (a == 2) {
      if (j) ret = max(ret, rec(i, j - 1, p, 2) + 1);
      ret = max(ret, rec(i, j, p ^ 1, 0));
    }
  }
  else {
    // should take at least one
    if (a == 0) {
      if (i) ret = min(ret, rec(i - 1, j, p, 1) - 1);
      if (j) ret = min(ret, rec(i, j - 1, p, 2) - 1);
    }
    // can take from first pillar or switch turn
    if (a == 1) {
      if (i) ret = min(ret, rec(i - 1, j, p, 1) - 1);
      ret = min(ret, rec(i, j, p ^ 1, 0));
    }
    // can take from second pillar or switch turn
    if (a == 2) {
      if (j) ret = min(ret, rec(i, j - 1, p, 2) - 1);
      ret = min(ret, rec(i, j, p ^ 1, 0));
    }
  }

  return dp[i][j][p][a] = ret;
}

void solve() {
  int A, B; cin >> A >> B >> K;

  for (int i = 0; i <= A; ++i) for (int j = 0; j <= B; ++j) {
    for (int p = 0; p < 2; ++p) for (int a = 0; a < 3; ++a) {
      dp[i][j][p][a] = INF + 1;
    }
  }

  if (rec(A, B, 0, 0) > 0) cout << "First\n";
  else cout << "Second\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
