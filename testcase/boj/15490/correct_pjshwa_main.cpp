#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3000;
int A[MAXN], dp[MAXN][MAXN][2][2];

// t = 0: kcm turn
// t = 1: ntopia turn
// p: kcm parity
int rec(int l, int r, int t, int p) {
  if (l > r) return t == p;
  if (dp[l][r][t][p] != -1) return dp[l][r][t][p];

  int res = 0;
  res |= !rec(l + 1, r, t ^ 1, t ? p : (p ^ A[l]));
  res |= !rec(l, r - 1, t ^ 1, t ? p : (p ^ A[r]));
  if (l < r) {
    res |= !rec(l + 2, r, t ^ 1, t ? p : (p ^ A[l] ^ A[l + 1]));
    res |= !rec(l, r - 2, t ^ 1, t ? p : (p ^ A[r] ^ A[r - 1]));
  }

  return dp[l][r][t][p] = res;
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i], A[i] %= 2;

  memset(dp, -1, sizeof dp);
  cout << (rec(0, N - 1, 0, 0) ? "Yes" : "No") << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
