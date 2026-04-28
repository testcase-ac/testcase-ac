#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 25, MAXV = 1e4;
ll dp[MAXV + 1];

void solve() {
  int N, V; cin >> N >> V;

  dp[0] = 1;
  for (int i = 1; i <= N; ++i) {
    int x; cin >> x;
    for (int v = x; v <= V; ++v) {
      dp[v] += dp[v - x];
    }
  }

  cout << dp[V] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
