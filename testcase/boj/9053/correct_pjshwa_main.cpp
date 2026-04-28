#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 10, INF = 0x3f3f3f3f;
int dp[1 << MAXN], T[MAXN], N, mask;

int rec(int state) {
  if (state == mask) return 0;
  if (dp[state] != -1) return dp[state];

  int ret = INF, cur = __builtin_popcount(state);
  for (int nstate = 1; nstate <= mask; ++nstate) {
    if (nstate & state) continue;

    vector<int> ts;
    for (int j = 0; j < N; ++j) {
      if (nstate & (1 << j)) ts.push_back(T[j]);
    }
    sort(ts.begin(), ts.end(), greater<int>());
    int maxt = 0, add = 0, Z = ts.size();
    for (int i = 0; i < Z; i += cur) {
      maxt = max(maxt, ts[i] + add++);
    }
    ret = min(ret, rec(state | nstate) + maxt);
  }
  return dp[state] = ret;
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; ++i) cin >> T[i];
  mask = (1 << N) - 1;

  memset(dp, -1, sizeof(dp));
  cout << rec(1) + T[0] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
