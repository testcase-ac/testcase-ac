#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 200;
const double INF = 1e18;
int a[MAX];
double d[MAX + 1][MAX + 1], icost[MAX + 1][MAX + 1];

double ival(int i, int j, int k) {
  return a[i] + (a[j] - a[i]) * (double)(k - i) / (j - i);
}

void solve() {
  int h, c;
  cin >> h >> c;
  for (int i = 0; i < h; i++) cin >> a[i];

  c -= 2;
  for (int i = 0; i <= h; i++) for (int j = 0; j <= h; j++) d[i][j] = INF;
  d[0][0] = 0;

  for (int i = 1; i < h - 1; i++) for (int k = 0; k < i; k++) {
    icost[k][i] = 0;
    for (int l = k + 1; l < i; l++) icost[k][i] += abs(a[l] - ival(k, i, l));
  }

  for (int i = 1; i < h - 1; i++) for (int j = 1; j <= c; j++) {
    for (int k = 0; k < i; k++) {
      double cost = icost[k][i] + d[k][j - 1];
      if (d[i][j] > cost) d[i][j] = cost;
    }
  }

  double ans = INF;
  for (int k = 0; k < h - 1; k++) {
    double cur = d[k][c];
    for (int i = k + 1; i < h; i++) cur += abs(a[i] - ival(k, h - 1, i));
    ans = min(ans, cur);
  }

  cout << fixed << setprecision(10) << ans / h << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
