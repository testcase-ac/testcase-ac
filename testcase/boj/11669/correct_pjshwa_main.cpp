#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 1e6, INF = 1e18;
int n, p, r;
ll dp[MAXN + 1];

ll rec(int v) {
  if (v == 1) return 0;
  if (dp[v] != -1) return dp[v];

  ll ret = INF;
  for (int d = 2; d <= v; ++d) {
    int nv = (v + d - 1) / d;
    ret = min(ret, rec(nv) + (ll)p * (d - 1) + r);
  }
  return dp[v] = ret;
}

void solve() {
  cin >> n >> r >> p;
  memset(dp, -1, sizeof(dp));
  cout << rec(n) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
