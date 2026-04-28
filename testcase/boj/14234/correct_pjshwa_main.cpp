#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
int n, dp[1 << 15][MAXN + 5], MAXT = 0;

// (start_time) -> (end_time, work_id)
vector<pii> W[MAXN + 5];

int rec(int s, int t) {
  if (t > MAXT) return 0;
  if (dp[s][t] != -1) return dp[s][t];

  int ret = rec(s, t + 1);
  for (auto [nt, wi] : W[t]) {
    if (s & (1 << wi)) continue;
    ret = max(ret, rec(s | (1 << wi), nt) + 1);
  }
  return dp[s][t] = ret;
}

void solve() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int a, b; cin >> a >> b;
    MAXT = max(MAXT, b);
    for (int j = a; j <= b; ++j) {
      int ti; cin >> ti;
      int e = j + ti - 1;
      if (e <= b) W[j].emplace_back(e, i);
    }
  }

  memset(dp, -1, sizeof dp);
  cout << rec(0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
