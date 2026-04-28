#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 18, INF = 1e9 + 7;
int d[1 << MAX][MAX];
int from[1 << MAX][MAX];
int w[MAX][MAX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) w[i][j] = INF;
  while (m--) {
    int a, b, c;
    cin >> a >> b >> c;
    w[a - 1][b - 1] = c;
  }

  for (int i = 0; i < (1 << n); i++) for (int j = 0; j < n; j++) d[i][j] = INF;
  d[1 << 0][0] = 0;

  for (int i = 1; i < (1 << n); i++) for (int j = 0; j < n; j++) {
    if (!(i & (1 << j))) continue;
    for (int k = 0; k < n; k++) {
      if (i & (1 << k)) continue;
      if (k == j) continue;

      int val = max(d[i][j], w[j][k]);
      if (val < d[i | (1 << k)][k]) {
        d[i | (1 << k)][k] = val;
        from[i | (1 << k)][k] = j;
      }
    }
  }

  int ans = INF, cur;
  for (int i = 1; i < n; i++) {
    int val = max(d[(1 << n) - 1][i], w[i][0]);
    if (val < ans) {
      ans = val;
      cur = i;
    }
  }

  if (ans == INF) cout << "-1\n";
  else {
    cout << ans << '\n';

    int state = (1 << n) - 1, idx = n;
    vector<int> traj;
    while (state) {
      traj.push_back(cur + 1);
      int tmp = state;
      state &= ~(1 << cur);
      cur = from[tmp][cur];
    }
    reverse(traj.begin(), traj.end());
    for (int e : traj) cout << e << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
