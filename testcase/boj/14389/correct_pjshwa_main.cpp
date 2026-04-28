#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 25, INF = 0x3f3f3f3f;
char board[MAX + 1][MAX + 1];
int dp[MAX + 1][1 << 10];
int N, M, mask;

int rec(int j, int pstate) {
  if (j == M) {
    if (pstate == mask) return 0;
    else return -INF;
  }
  if (dp[j][pstate] != -1) return dp[j][pstate];

  int ret = -INF;
  vector<int> spoints, PV;
  for (int i = 0; i < N; i++) {
    PV.push_back((pstate & (1 << i)) ? 1 : 0);
  }

  // check if all pstate's holes are even spaced
  {
    int i = 0;
    while (i < N) {
      int cur = PV[i];
      if (cur == 1) i++;
      else {
        if (i < N - 1 && PV[i + 1] == 0) {
          spoints.push_back(i);
          i += 2;
        }
        else return dp[j][pstate] = -INF;
      }
    }
  }

  for (int nstate = 0; nstate <= mask; ++nstate) {
    vector<int> NV;
    for (int i = 0; i < N; i++) {
      NV.push_back((nstate & (1 << i)) ? 1 : 0);
    }
    
    bool able = true;
    for (int i = 0; i < N; ++i) {
      if (NV[i] == 0 && board[i][j] == '1') able = false;
    }
    if (!able) continue;

    for (int si : spoints) {
      if (NV[si] == 1 || NV[si + 1] == 1) able = false;
    }
    if (!able) continue;

    int t = __builtin_popcount(nstate) + spoints.size() * 16;
    int nstate_real = nstate;
    for (int i = 0; i < N; ++i) {
      if (!(pstate & (1 << i))) nstate_real |= (1 << i);
    }
    ret = max(ret, t + rec(j + 1, nstate_real));
  }
  return dp[j][pstate] = ret;
}

void solve() {
  cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> board[i];
  mask = (1 << N) - 1;

  if (N == 1 || M == 1) cout << N * M << '\n';
  else {
    int ans = 0;

    memset(dp, -1, sizeof(dp));
    for (int state = 0; state <= mask; ++state) {
      bool able = true;
      for (int i = 0; i < N; ++i) {
        if (!(state & (1 << i)) && board[i][0] == '1') {
          able = false;
          break;
        }
      }
      if (able) ans = max(ans, __builtin_popcount(state) + rec(1, state));
    }
    cout << ans << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
