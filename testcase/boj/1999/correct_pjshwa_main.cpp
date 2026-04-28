#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 250;
int board[MAX + 1][MAX + 1];
int mpf[MAX + 1][MAX + 1], xpf[MAX + 1][MAX + 1];

void solve() {
  int n, b, k;
  cin >> n >> b >> k;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> board[i][j];

  for (int i = 1; i <= n; i++) {
    priority_queue<pii> px;
    priority_queue<pii, vector<pii>, greater<pii>> pm;
    for (int j = 1; j <= b; j++) {
      px.push({board[i][j], j});
      pm.push({board[i][j], j});
    }
    xpf[i][1] = px.top().first, mpf[i][1] = pm.top().first;

    for (int j = b + 1; j <= n; j++) {
      px.push({board[i][j], j});
      pm.push({board[i][j], j});
      while (px.top().second <= j - b) px.pop();
      while (pm.top().second <= j - b) pm.pop();

      xpf[i][j - b + 1] = px.top().first, mpf[i][j - b + 1] = pm.top().first;
    }
  }

  while (k--) {
    int x, y;
    cin >> x >> y;

    int xval = 0, mval = 1e9;
    for (int i = x; i <= x + b - 1; i++) {
      xval = max(xval, xpf[i][y]);
      mval = min(mval, mpf[i][y]);
    }

    cout << xval - mval << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
