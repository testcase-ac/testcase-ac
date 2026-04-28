#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
ll A[MAX], L, V;
ll cost[MAX][MAX];

// current index, last index, start point
ll dp[MAX][MAX][MAX];

ll rec(int i, int j, int k) {
  if (dp[i][j][k] != -1) return dp[i][j][k];
}

ll d_between(int s, int e) {
  ll ret = 0;
  if (s > e) {
    for (int i = s; i < V; ++i) {
      ret += min(A[i] - A[s], L + A[e] - A[i]);
    }
    for (int i = 0; i <= e; ++i) {
      ret += min(A[e] - A[i], L + A[i] - A[s]);
    }
  }
  else {
    for (int i = s; i <= e; ++i) {
      ret += min(A[i] - A[s], A[e] - A[i]);
    }
  }
  return ret;
}

void solve() {
  int P; cin >> V >> P >> L;
  for (int i = 0; i < V; ++i) cin >> A[i];
  for (int s = 0; s < V; ++s) for (int e = 0; e < V; ++e) {
    cost[s][e] = d_between(s, e);
  }

  ll ans = 1e18, as, ae;
  memset(dp, -1, sizeof(dp));
  for (int s = 0; s < V; ++s) for (int e = s; e < V; ++e) {

  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
