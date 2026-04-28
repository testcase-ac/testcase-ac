#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, MOD = 1e9 + 9;
int d[MAX + 1][4];

void solve() {
  int n;
  cin >> n;
  
  int ans = 0;
  for (int t = 1; t <= 3; t++) ans = (ans + d[n][t]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  d[1][1] = 1;
  d[2][2] = 1;
  d[3][1] = d[3][2] = d[3][3] = 1;
  for (int i = 4; i <= MAX; i++) {
    for (int f = 1; f <= 3; f++) for (int t = 1; t <= 3; t++) {
      if (f == t) continue;
      d[i][t] = (d[i][t] + d[i - t][f]) % MOD;
    }
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
