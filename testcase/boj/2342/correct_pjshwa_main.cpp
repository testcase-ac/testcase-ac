#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, INF = 1e9 + 7;
int n, a[MAX + 1], d[MAX + 1][25];

int f(int f1, int f2) {
  if (f1 == 0) return 2;
  if (f1 == f2) return 1;
  if (f1 == 1 || f1 == 3) {
    if (f2 == 1 || f2 == 3) return 4;
    else return 3;
  }
  if (f1 == 2 || f1 == 4) {
    if (f2 == 2 || f2 == 4) return 4;
    else return 3;
  }
}

int main() {
  fast_io();

  while (1) {
    int x;
    cin >> x;
    if (x == 0) break;

    a[++n] = x;
  }

  for (int i = 0; i <= n; i++) for (int j = 0; j < 25; j++) d[i][j] = INF;
  d[0][0] = 0;

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 25; j++) {
      int lf = j / 5, rf = j % 5;
      if (rf != a[i]) d[i][a[i] * 5 + rf] = min(d[i][a[i] * 5 + rf], d[i - 1][j] + f(lf, a[i]));
      if (lf != a[i]) d[i][lf * 5 + a[i]] = min(d[i][lf * 5 + a[i]], d[i - 1][j] + f(rf, a[i]));
    }
  }

  int ans = INF;
  for (int i = 0; i < 25; i++) ans = min(ans, d[n][i]);
  cout << ans;
}
