#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3000;
// d[i][j][k]: i th player failed on slot j, and the last state of slot j is k
// k = 0: two glasses left
// k = 1: one glass left
double d[457][MAX + 1][2];

void solve() {
  int n, k;
  cin >> n >> k;

  d[1][1][0] = 2.0 / 3;
  for (int j = 2; j <= n; j++) d[1][j][0] = d[1][j - 1][0] / 3;
  for (int i = 2; i <= k; i++) for (int j = 1; j <= n; j++) {
    d[i][j][0] += d[i - 1][j - 1][0] / 3 + d[i - 1][j - 1][1] * 2 / 3;
    d[i][j][0] += d[i][j - 1][0] / 3;
    d[i][j][1] = d[i - 1][j][0] / 2;
  }

  double fprob = 0;
  for (int j = 1; j <= n; j++) fprob += d[k][j][0] + d[k][j][1];
  cout << fixed << setprecision(10) << 1 - fprob << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
