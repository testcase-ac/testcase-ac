#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20;
int board[MAX][MAX];
ll csum[MAX];

void solve() {
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    cin >> board[i][j];
    csum[j] += board[i][j];
  }

  ll ans = -1e18, acc[n];
  for (int rstate = 0; rstate < (1 << n); rstate++) {
    memset(acc, 0, sizeof(acc));

    for (int i = 0; i < n; i++) {
      if (rstate & (1 << i)) {
        for (int j = 0; j < n; j++) acc[j] += board[i][j];
      }
    }

    ll cur = 0;
    for (int j = 0; j < n; j++) cur += min(acc[j], csum[j] - acc[j]);
    ans = max(ans, cur);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
