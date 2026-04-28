#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 12, MAXL = 50;
int B_mask[MAXN][MAXN];
int X[MAXN], Y[MAXN], ban[MAXN];
int dp[MAXN][1 << MAXN][MAXL];

void solve() {
  int L, N; cin >> L >> N;

  memset(ban, 0, sizeof(ban));
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    int idx = (x - 1) * 4 + (y - 1);
    ban[idx] = 1;
  }
  if (L > MAXL) return cout << "BAD MEMORY\n", void();

  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < 12; ++i) {
    if (!ban[i]) dp[i][1 << i][0] = 1;
  }

  for (int state = 0; state < (1 << 12); ++state) for (int nxt = 0; nxt < 12; ++nxt) {
    if (ban[nxt] || (state & (1 << nxt))) continue;

    for (int pre = 0; pre < 12; ++pre) {
      if (ban[pre] || !(state & (1 << pre))) continue;

      int mask = B_mask[pre][nxt], nstate = (state | (1 << nxt));
      if ((nstate & mask) != mask) continue;

      int dis = abs(X[pre] - X[nxt]) + abs(Y[pre] - Y[nxt]);
      for (int pl = dis; pl <= MAXL; ++pl) {
        if (dp[pre][state][pl - dis] == 0) continue;
        dp[nxt][nstate][pl] += dp[pre][state][pl - dis];
      }
    }
  }

  int ans = 0;
  for (int state = 0; state < (1 << 12); ++state) for (int i = 0; i < 12; ++i) {
    int cnt = __builtin_popcount(state);
    if (cnt > 1) ans += dp[i][state][L];
  }

  if (ans == 0) cout << "BAD MEMORY\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  for (int i = 0; i < 12; ++i) {
    X[i] = (i / 4) + 1;
    Y[i] = (i % 4) + 1;
  }

  for (int si = 0; si < 12; ++si) for (int ei = 0; ei < 12; ++ei) {
    int sx = X[si], sy = Y[si], ex = X[ei], ey = Y[ei];
    int maxx = max(sx, ex), minx = min(sx, ex);
    int maxy = max(sy, ey), miny = min(sy, ey);
    B_mask[si][ei] = (1 << ei);

    for (int p = 0; p < 12; ++p) {
      if (p == si || p == ei) continue;
      int px = X[p], py = Y[p];
      if (px < minx || maxx < px || py < miny || maxy < py) continue;

      int dx = ex - sx, dy = ey - sy;
      int dx1 = px - sx, dy1 = py - sy;
      if (dx1 * dy == dy1 * dx) B_mask[si][ei] |= (1 << p);
    }
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
