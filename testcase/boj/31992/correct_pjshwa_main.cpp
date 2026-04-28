#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 15, MAXM = 1000, INF = 0x3f3f3f3f;
int C[MAXM + 1], R[MAXN][MAXM], mCost[1 << MAXN];

void solve() {
  int N, M; cin >> N >> M;
  for (int j = 0; j < M; ++j) cin >> C[j];
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> R[i][j];

  memset(mCost, 0x3f, sizeof(mCost)); mCost[0] = 0;
  for (int j = 0; j < M; ++j) for (int mask = 1; mask < (1 << N); ++mask) {
    int ok = 1, cnt = __builtin_popcount(mask);
    for (int i = 0; i < N; ++i) {
      if (!(mask & (1 << i))) continue;
      if (R[i][j] * cnt < C[j]) ok = 0;
    }
    if (ok) mCost[mask] = min(mCost[mask], C[j]);
  }
  for (int x = 0; x < (1 << N); ++x) for (int i = x; i > 0; i = (i - 1) & x) {
    mCost[x] = min(mCost[x], mCost[x ^ i] + mCost[i]);
  }

  int ans = mCost[(1 << N) - 1];
  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
