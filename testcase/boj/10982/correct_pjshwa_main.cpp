#include <bits/stdc++.h>
#define u(a,b) a=min(a,b)
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MAXN = 1000, MAXH = 100, INF = 1e9 + 7;
int d[3][MAXN * MAXH + 1];
int main() {
  fast_io();

  int t;
  cin >> t;

  while (t--) {
    int n, ai, bi;
    cin >> n;

    d[0][0] = 0;
    for (int j = 1; j <= MAXN * MAXH; j++) d[0][j] = INF;

    int ci = 0, ni;
    while (n--) {
      cin >> ai >> bi;

      ni = (ci + 1) % 3;
      for (int j = 0; j <= MAXN * MAXH; j++) d[ni][j] = INF;
      for (int j = 0; j <= MAXN * MAXH; j++) {
        u(d[ni][j + ai], d[ci][j]);
        u(d[ni][j], d[ci][j] + bi);
      }

      ci = ni;
    }

    int ans = INF;
    for (int j = 0; j <= MAXN * MAXH; j++) ans = min(ans, max(j, d[ci][j]));
    cout << ans << '\n';
  }
}
