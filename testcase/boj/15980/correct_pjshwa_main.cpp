#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000, INF = 1e9 + 7;
int w[MAX + 1][MAX + 1], p[MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    string dir, s;
    cin >> dir >> s;
    for (int j = 0; j < m; j++) {
      if (s[j] == '1') w[i][j] = dir == "L" ? -1 : 1;
      p[j] += w[i][j];
    }
  }

  int ans = INF, idx = -1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < m; j++) p[j] -= w[i][j];

    int cur = 0, run = 0;
    for (int j = 0; j < m; j++) {
      run += p[j];
      cur = max(cur, abs(run));
    }

    if (ans > cur) ans = cur, idx = i;

    for (int j = 0; j < m; j++) p[j] += w[i][j];
  }

  cout << idx << '\n' << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
