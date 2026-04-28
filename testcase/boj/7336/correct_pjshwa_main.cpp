#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 15, MAXC = 20;
int N, ULx[MAXN], ULy[MAXN], DRx[MAXN], DRy[MAXN], C[MAXN];
int dp[1 << MAXN][MAXC + 1], mask;

bool colorable(int i, int state) {
  for (int j = 0; j < N; ++j) {
    if (i == j || (state & (1 << j))) continue;
    if (DRy[j] != ULy[i]) continue;
    if (ULx[i] < DRx[j] && DRx[i] > ULx[j]) return false;
  }
  return true;
}

int rec(int state, int c) {
  if (state == mask) return 0;
  if (dp[state][c] != -1) return dp[state][c];

  int ret = N;
  for (int i = 0; i < N; ++i) {
    if (state & (1 << i) || !colorable(i, state)) continue;
    ret = min(ret, rec(state | (1 << i), C[i]) + (c != C[i]));
  }
  return dp[state][c] = ret;
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> ULy[i] >> ULx[i] >> DRy[i] >> DRx[i] >> C[i];
  }
  mask = (1 << N) - 1;

  memset(dp, -1, sizeof(dp));
  cout << rec(0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
