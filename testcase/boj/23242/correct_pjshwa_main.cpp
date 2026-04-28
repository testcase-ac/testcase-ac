#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 4000;
const double INF = 1e18;
int a[MAX + 1];
ll pfq[MAX + 1], pfs[MAX + 1];
double d[MAX + 1][30];

double error(int s, int e) {
  int d = e - s + 1;
  ll sq = pfq[e] - pfq[s - 1], ss = pfs[e] - pfs[s - 1];
  double mean = (double)ss / d;
  return sq - d * mean * mean;
}

void solve() {
  int b, n;
  cin >> b >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    pfq[i] = pfq[i - 1] + a[i] * a[i];
    pfs[i] = pfs[i - 1] + a[i];
  }

  for (int i = 1; i <= n; i++) for (int j = 0; j < b; j++) d[i][j] = INF;
  for (int i = 1; i <= n; i++) {
    d[i][0] = error(1, i);
    for (int j = i - 1; j >= 1; j--) for (int k = 1; k < b; k++) {
      d[i][k] = min(d[i][k], d[j][k - 1] + error(j + 1, i));
    }
  }

  double ans = INF;
  for (int k = 0; k < b; k++) ans = min(ans, d[n][k]);
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
